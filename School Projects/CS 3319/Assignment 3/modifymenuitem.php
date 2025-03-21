<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 4 | Assignment 3</title>
</head>
<body>

<!-- Include statements -->
<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 4</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Allow the user to modify the price and calorie count of a menu item.</li>
<li>Ensure the inputs from the user are correct.</li>
</ol>

<!-- Creating user input spaces -->
<form action="modifydata.php" method="post">

<label><b>Input Menu Item ID to be Modified:</b></label>
<br>
<input type="text" name="menuitem">

<br>
<br>

<label><b>Input New Price:</b></label>
<br>
<input type="number" name="price" min="0" step=".01" required>

<br>
<br>

<label><b>Input New Calorie Count:</b></label>
<br>
<input type="number" name="caloriecount" min="0" required>

<br>
<br>

<input type="submit" value="Submit Modification">

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
