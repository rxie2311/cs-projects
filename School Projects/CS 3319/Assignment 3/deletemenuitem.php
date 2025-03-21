<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 3 | Assignment 3</title>
</head>
<body>

<!-- Include statements -->
<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 3</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Allow the user to delete a menu item.</li>
<li>Ask the user for confirmation of deletion.</li>
<li>Throw an error if the menu item is in an order already.</li>
</ol>

<!-- Creating user input spaces -->
<form action="deletedata.php" method="post">

<label><b>Input Menu Item ID to be Deleted:</b></label>
<br>
<input type="text" name="menuitem">

<br>
<br>

<label><b>Are you sure you wish to delete this item?</b></label>
<br>
<label><input type='radio' name='confirm' value='yes' required> Yes</label>
<br>
<label><input type='radio' name='confirm' value='no'> No</label>

<br>
<br>

<input type="submit" value="Submit Deletion">

</form>

<br>
<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>

<!-- Disconnect from database -->
<?php
mysqli_close($connection);
?>


</body>
</html>
