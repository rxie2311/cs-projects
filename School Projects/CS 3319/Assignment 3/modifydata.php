<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 4 | Assignment 3</title>
</head>
<body>

<?php
include 'connecttodb.php';
?>

<?php
// Taking user inputs from the text box
$uMenuItemID = $_POST['menuitem'];
$uPrice = $_POST['price'];
$uCalories = $_POST['caloriecount'];

// Confirming that the menu item id entered exists
$query = 'SELECT * FROM menuitem WHERE menuitemid = "' . $uMenuItemID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) <= 0) {
        die("Error: Menu Item ID entered does not exist.");
}

// Modifying the menuitem table
$query = 'UPDATE menuitem SET price = ' . $uPrice . ', caloriecount = ' . $uCalories . ' WHERE menuitemid = "' . $uMenuItemID . '"';
$result = mysqli_query($connection,$query);
if (!$result) {
	die("Error: Update query error.");
}

// Displaying the new updated menu item
echo '<h3>Successfully modified the menu item!</h3>';
echo '<b>Here is your newly updated item:</b><br>';

$query = 'SELECT * FROM menuitem WHERE menuitemid = "' . $uMenuItemID . '"';
$result = mysqli_query($connection,$query);
$row = mysqli_fetch_assoc($result);

echo '<b>Menu Item ID: </b>' . $row['menuitemid'] . '<br>';
echo '<b>Dish Name: </b>' . $row['dishname'] . '<br>';
echo '<b>NEW Price per Item: </b>$' . $row['price'] . '<br>';
echo '<b>NEW Calorie Count: </b>' . $row['caloriecount'] . '<br>';
echo '<b>Vegetarian: </b>' . $row['veggie'] . '<br>';

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
