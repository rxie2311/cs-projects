<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 3 | Assignment 3</title>
</head>
<body>

<?php
include 'connecttodb.php';
?>

<?php
// Taking user inputs from the text box and confirm button
$uMenuItemID = $_POST['menuitem'];
$confirm = $_POST['confirm'];

// Checking if the user inputted menu item even exists
$query = 'SELECT * FROM menuitem WHERE menuitemid = "' . $uMenuItemID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) <= 0) {
        die("Error: Menu Item ID entered does not exist.");
    }

// Checks if the user inputted menu item is in an order
$query = 'SELECT * FROM overallorder WHERE menuitemid = "' . $uMenuItemID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) > 0) {
        die("Error: Menu Item is in an order, it cannot be deleted.");
}

// Checks if the user selected yes to confirm deletion
if ($confirm == 'yes') {
	$query = 'DELETE FROM menuitem WHERE menuitemid = "' . $uMenuItemID . '"';
	$result = mysqli_query($connection,$query);
	if (!$result) {
        	die("Error: Deletion query error.");
   	} else {
		echo '<h3>Deletion successful!</h3>';
		echo 'You may return to the main menu now. <br>';
	}
} else {
	echo '<h3>Deletion cancelled!</h3>';
	echo 'You may return to the main menu now. <br>';
}

// Close the connection
mysqli_close($connection);
?>

<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
