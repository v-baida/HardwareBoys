<!DOCTYPE html>
<html>
<head>
<meta name="keywords" content="" />
<meta name="description" content="" />
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>Chernihiv Parking System</title>
<link href="http://fonts.googleapis.com/css?family=Oxygen:400,700,300" rel="stylesheet" type="text/css" />
<link href="style.css" rel="stylesheet" type="text/css" media="screen" />
</head>
<body>
<div id="wrapper">
	<div id="logo" class="container">
		<h1><a href="#">Hardware boys</a></h1>
		<p>Chernihiv Parking System</p>
	</div>
	<div id="three-column" class="container">
<?php
define("PARKING_PLACES", 4); //Enter countity of parking places
$servername = "localhost";

// Db connection data
$dbname = "id16422268_che_parking_system";
$username = "id16422268_hardware_boy";
$password = "F2KZJEb/sX*&O@vE";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

// Get last string from DB
$sql = "SELECT * 
		FROM sensors_data 
		ORDER BY id DESC 
		LIMIT 1";

//init values
$row_id = $sensor1 = $sensor2 = $sensor3 = $sensor4 = $counter = 0;
$row_date = "";
$sensors_data = array();
// Organize data
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_date = $row["date"];

		$sensor1 = $row["sensor1"];
		$sensors_data["Parking place 1"] = $sensor1;
    
		$sensor2 = $row["sensor2"];
		$sensors_data["Parking place 2"] = $sensor2;
        
		$sensor3 = $row["sensor3"];
		$sensors_data["Parking place 3"] = $sensor3;
        
		$sensor4 = $row["sensor4"]; 
		$sensors_data["Parking place 4"] = $sensor4;
		}
	$result->free();
}
$conn->close();

$counter = 0;
foreach($sensors_data as $key => $value) {

}

foreach($sensors_data as $key => $value) {
	switch($value) {
		case 0:
			//Place are free
			echo '<div class="tbox">
			<div class="box-style box-style02" id="place_free" style="background-color: rgb(152,251,152);">
				<div class="content">
					<h3 style="color: black;">'.$key.'</h3>
					<div class="image" id="place_free_img" style="background-image: url();
																  background-repeat: no-repeat;
																  background-position: center;
																  height: 536px;">
					</div>
				</div>
			</div>
		</div>';
			break;
		case 1: 
			//Place are busy
			echo '<div class="tbox">
			<div class="box-style box-style01" id="place_busy" style="background-color: rgb(255,0,0);">
				<div class="content">
					<h3 style="color: white;">'.$key.'</h3>
					<div class="image" id="place_busy_img" style="background-image: url(/images/bg_true.png);
																  background-repeat: no-repeat;
																  background-position: center;
																  height: 536px;">
					</div>
				</div>
			</div>
		</div>';
			break;
		default:
			//Place are busy if something went wrong
			echo '<div class="tbox">
			<div class="box-style box-style01" id="place_busy" style="background-color: rgb(152,251,152);">
				<div class="content">
					<h3 style="color: white;>'.$key.'</h3>
					<div class="image" id="place_busy_img" style="background-image: url(/images/bg_true.png);
																  background-repeat: no-repeat;
																  background-position: center;
																  height: 536px;">
					</div>
				</div>
			</div>
		</div>';
	}
}

echo '
	</div>
	</div>	
</div>
	<script>
	function myFunction() {
		window.location.reload();
	}

	myFunction.call();
	</script>
</body>
</html>';
?>