<html>
   <head>
      <title>Data of Sensor</title>
   </head>
   <body>
      <h1>Water Level Data</h1>
         <hr>
      <?php
         include("db_connection.php");
         $link=Connection();
         $result=mysqli_query($link,"select * from stickwaterleveldata order by id desc");
      ?>
      <table border="1" cellspacing="1" cellpadding="1">
         <tr>
            <td>&nbsp;Water Level&nbsp;</td>
            <td>&nbsp;Water Present&nbsp;</td>
            <td>&nbsp;Device Type&nbsp;</td>
          </tr>
         <?php     
            while($row = mysqli_fetch_array($result)) {
               printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp;</td></tr>", $row["waterlevel"], $row["water_present"], $row["DeviceType"]);
            }
            mysqli_free_result($result);
         ?>
      </table>
   </body>
</html>