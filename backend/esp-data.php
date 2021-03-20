<!DOCTYPE html>
<html>
<body>
<?php
$servername = "localhost";

// REPLACE with your Database name
$dbname = "id16422268_che_parking_system";
// REPLACE with Database user
$username = "id16422268_hardware_boy";
// REPLACE with Database user password
$password = "F2KZJEb/sX*&O@vE";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, date, sensor1, sensor2, sensor3, sensor4 FROM sensors_data ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr>
        <td>ID</td> 
        <td>Date</td> 
        <td>Sens1</td> 
        <td>Sens2</td> 
        <td>Sens3</td>
        <td>Sens4</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_date = $row["date"];
        $sensor1 = $row["sensor1"];
        $sensor2 = $row["sensor2"];
        $sensor3 = $row["sensor3"];
        $sensor4 = $row["sensor4"]; 
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_date . '</td> 
                <td>' . $sensor1 . '</td> 
                <td>' . $sensor2 . '</td> 
                <td>' . $sensor3 . '</td>
                <td>' . $sensor4 . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>