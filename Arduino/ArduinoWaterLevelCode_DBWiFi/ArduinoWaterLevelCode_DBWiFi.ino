// Code loosely based off of the following code referenced by the links below
// source: http://www.electroschematics.com/9964/arduino-water-level-sensor/
// http://www.electroschematics.com/9964/arduino-water-level-indicator-controller/

// Added WiFi connectivity to tihs code to allow communication to a MySQL server
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__
char pass[] = "your-password"; //password Wi-Fi
char ssid[] = "your-ssid"; //name Wi-Fi
int status = WL_IDLE_STATUS;
#endif

// Need to be careful which digital I/O pins are used when
// using the Arduino WiFi Shield as the WiFiShield uses some of them
//
// https://www.arduino.cc/en/Main/ArduinoWiFiShield

byte sensorPin[] = {5, 6, 8, 9};

const byte sensors = 4;
int waterlevel = 0;
boolean water_present; 

char server[] = "www.iot-detroit.org";
IPAddress local_ip;

// Initialize the client library
WiFiClient client;
 
void setup() {
  Serial.begin(9600); // initialize the serial port
  
  for(int i = 0; i < sensors; i++) {
     pinMode(sensorPin[i], INPUT_PULLUP); 
  }

// check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {

    // Make an HTTP request:
    client.print("GET HTTP/1.1\r\n");
    client.print("Host: www.iot-detroit.org\r\n");
    client.print("Connection: close\r\n\r\n");
    client.stop();
  }
}
 
void loop() {
  waterlevel = 0;
  water_present = false;

  // loop through the sensor pins and break when we
  // find one that is low
  // The sensor pin will be low when it is submerged
  // in water as we have the GND pin at the bottom of
  // the bucket
  // The first pin should be connected to the wire that
  // is the highest as we break once a LOW is returned
  // as we assume all wires below the submberged will also
  // be submerged
  for(int i = 0; i < sensors; i++) {
    waterlevel=i;
    Serial.print(i);
    if(digitalRead(sensorPin[i]) == LOW) {
        water_present = true;
        break;
    }
  }
  Serial.println("----");

  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()&& status == WL_CONNECTED) {
    char c = client.read();
    Serial.write(c);
  }
  client.flush();
  client.stop();

  if (client.connect(server,80) == 1) {

    // HTTP requests are very picky on the format so pay attention
    // to everyghing including spaces!!
    client.print( "GET /Water-Level-IoT-Tests/php/StickWaterLevelRead_MySQL/addwaterleveldata.php?");
    client.print("level=");
    client.print( waterlevel );
    client.print("&");
    client.print("water_present=");
    client.print( water_present );
    client.print("&");
    client.print("DeviceType=");
    client.print("ArduinoUNOWiFi" );
    client.print( " HTTP/1.1\r\n");
    client.print( "Host: www.iot-detroit.org\r\n\r\n" );
    
    Serial.print( "GET /Water-Level-IoT-Tests/php/StickWaterLevelRead_MySQL/addwaterleveldata.php?");
    client.print("level=");
    client.print( waterlevel );
    client.print("&");
    client.print("water_present=");
    client.print( water_present );
    client.print("&");
    client.print("DeviceType=");
    client.print("ArduinoUNOWiFi" );
    Serial.print( " HTTP/1.1\r\n");
    Serial.print( "Host: www.iot-detroit.org\r\n" );

  }
  else {
    Serial.println("Disconnected");
  }

  delay(5000);  
 }

 
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
