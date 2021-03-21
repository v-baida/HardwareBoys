<!DOCTYPE html>
<html>
<head>
<meta name="keywords" content="" />
<meta name="description" content="" />
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>Chernihiv Parking System</title>
<link href="http://fonts.googleapis.com/css?family=Oxygen:400,700,300" rel="stylesheet" type="text/css" />
<link href="style.css" rel="stylesheet" type="text/css" media="screen" />
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
</head>
<body>
<div id="wrapper">
	<div id="logo" class="container">
		<div class="row">
		<div class="col-sm-12">
		<h1><a href="#">Hardware boys</a></h1>
		<p>Chernihiv Parking System</p>
       </div>
	   </div>
	</div>
<?php
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
$sensors_data_nums = array();
// Organize data
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_date = $row["date"];

		$sensor1 = $row["sensor1"];
		$sensors_data["Parking place 1"] = $sensor1;
		$sensors_data_nums[1] = $sensor1;

		$sensor2 = $row["sensor2"];
		$sensors_data["Parking place 2"] = $sensor2;
        $sensors_data_nums[2] = $sensor2;

		$sensor3 = $row["sensor3"];
		$sensors_data["Parking place 3"] = $sensor3;
        $sensors_data_nums[3] = $sensor3;

		$sensor4 = $row["sensor4"]; 
		$sensors_data["Parking place 4"] = $sensor4;
		$sensors_data_nums[4] = $sensor4;	
	}
	$result->free();
}
$conn->close();


$counterFree = 0; //counter of free spaces
$placesFree = array(); //arrays for nums of free spaces
foreach($sensors_data_nums as $key => $value) {
	if($value == 0) {
		$counterFree++;
	}

	if($value == 0) {
		//store places
		array_push($placesFree, $key);
	}
}
echo '<div class="container">
	  <div class="row">';
echo '<div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 col-12"';
	 echo '<p>Free parking spaces: ';
	  foreach($placesFree as $item) {
		if($item != end($placesFree)) {
			echo $item.', ';
		} else {
			echo $item.' '; //print last element without separator
		}
	  }
	 echo '<br>Total free spaces: '.$counterFree;
	 echo '</p>';
echo '</div>';
echo '</div>';
echo '</div>';

echo '<div class="container">
	  <div class="row">';
foreach($sensors_data as $key => $value) {
	switch($value) {
		case 0:
			//Place are free

			//Play with width: 75% CSS
			echo '<div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 col-12">
				  <h4 class="text-center">'.$key.'</h4>
				  <div class="layer" style="background-color: rgb(144,238,144)">
					<img src="/images/clear_bg.png" style="display: block;
					margin-left: auto;
					margin-right: auto;
					width: 75%;"> 
				  </div>
				  </div>';
			break;
		case 1: 
			//Place are busy
			echo '<div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 col-12">
				  <h4 class="text-center">'.$key.'</h4>
				  <div class="layer" style="background-color: rgb(255,0,0)">
					<img src="/images/bg_true.png" style="display: block;
					margin-left: auto;
					margin-right: auto;
					width: 75%;">
				  </div>
				  </div>';
			break;
		default:
			//Place are busy if something went wrong
			echo '<div class="col-xl-3 col-lg-3 col-md-3 col-sm-6 col-12">
				  <h4 class="text-center">'.$key.'</h4>
				  <div class="layer" style="background-color: rgb(255,0,0)">
					<img src="/images/bg_true.png" style="display: block;
					margin-left: auto;
					margin-right: auto;
					width: 75%">
				  </div>
				  </div>';
	}
}
echo '
		</div>	
	</div>
</div>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
</body>
</html>';
/*
<script>
	function myFunction() {
		window.location.reload();
	}

	myFunction.call();
</script>
*/
?>