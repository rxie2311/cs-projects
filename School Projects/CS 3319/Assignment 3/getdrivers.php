<?php
include 'connecttodb.php';
?>

<?php
// Making a query for drivers that have not delivered before
$query = 'SELECT driver.firstname, driver.lastname, driver.driverid AS dID FROM driver LEFT JOIN cusorder ON cusorder.driverid = driver.driverid WHERE cusorder.driverid IS NULL';
$result=mysqli_query($connection,$query);
if (!$result) {
         die("Error: Query failed.");
}

// While loop to output all the driver info
echo '<h3>Driver Details:</h3>';
while ($row=mysqli_fetch_assoc($result)) {
	echo '<b>Driver ID: </b>' . $row['dID'] . '<br>';
	echo '<b>First Name: </b>' . $row['firstname'] . '<br>';
	echo '<b>Last Name: </b>' . $row['lastname'] . '<br><br>';
}
mysqli_free_result($result);

// Close the connection
mysqli_close($connection);
?>
