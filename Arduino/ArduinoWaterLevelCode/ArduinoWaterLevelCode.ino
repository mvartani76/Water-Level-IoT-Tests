// Code loosely based off of the following code referenced by the links below
// source: http://www.electroschematics.com/9964/arduino-water-level-sensor/
// http://www.electroschematics.com/9964/arduino-water-level-indicator-controller/


byte sensorPin[] = {5, 6, 7, 8};

const byte sensors = 4;
int level = 0; 
 
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < sensors; i++) {
    // Use the internal pullup resistors on the input
    // pins so they are not floating and give random
    // values
    pinMode(sensorPin[i], INPUT_PULLUP); 
  }
}
 
void loop() {
  level = 0; 
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
    level=i;
    Serial.print(i);
     if(digitalRead(sensorPin[i]) == LOW) {
        break;
     }
     level=i+1;
  }
  Serial.println("----");
 
  switch(level) {
    case 0:
      Serial.println("Black Wire - Pin 5");
      break;
    case 1:
       Serial.println("Yellow Wire - Pin 6");
       break;
    case 2:
       Serial.println("Blue Wire - Pin 7");
       break;
    case 3:
       Serial.println("White Wire - Pin 8");
       break;
    case 4:
       Serial.println("NO WATEr");
       break;
    default:
      Serial.println("NO WATER"); 
      break;
  }
  delay(2000);
}
