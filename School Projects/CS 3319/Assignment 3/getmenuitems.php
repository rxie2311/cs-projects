<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>View Order | Assignment 3</title>
</head>
<body>

<?php
include 'connecttodb.php';
?>

<?php
// Taking the user input from the radio buttons
$whichAttr = $_POST['attribute'];
$whichOrder = $_POST['order'];

// Query to create the user sorted menuitem table
$query = 'SELECT * FROM menuitem ORDER BY ' . $whichAttr . ' ' . $whichOrder;
$result = mysqli_query($connection,$query);
if (!$result) {
         die("database query failed.");
     }

// Telling the user what they sorted by
echo '<h3>Your Sort Options:</h3>';
echo 'Attribute: ' . $whichAttr;
echo '<br>';
echo 'Order: ' . $whichOrder;
echo '<br>';

// Listing out the user sorted menuitem table
echo '<h3>Table Format: Menu Item ID -- Dish Name -- Price -- Calories -- Vegetarian</h3>';
while ($row=mysqli_fetch_assoc($result)) {
        echo $row["menuitemid"] . ' -- ' . $row["dishname"] . ' -- $' . $row["price"] . ' -- ' . $row["caloriecount"] . ' -- ' . $row["veggie"];
	echo '<br>';
	echo '<br>';
     }
     mysqli_free_result($result);
?>

<?php
mysqli_close($connection);
?>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
