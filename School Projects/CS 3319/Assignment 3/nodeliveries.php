<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 5 | Assignment 3</title>
</head>
<body>

<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 5</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Allow the user to see the driver id, first name and last name of all drivers who have not made a delivery before.</li>
</ol>

<?php
include 'getdrivers.php';
?>

<br>
<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
