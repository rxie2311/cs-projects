<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>View Order | Assignment 3</title>
</head>
<body>

<!-- Main header -->
<h1>Your Order Has Been Inserted!</h1>

<!-- Small description header -->
<h3>The details of your inserted order is listed below:</h3>

<?php
include 'connecttodb.php';
?>

<?php
// Getting the order id from the redirect link
$orderid = $_GET['orderid'];

// Showing the details of the order the user added
$query = 'SELECT * FROM cusorder WHERE orderid = "' . $orderid . '"';
$result=mysqli_query($connection,$query);
    if (!$result) {
         die("Error: Query failed.");
     }

echo '<h4>User Order Details:</h4>';
while ($row=mysqli_fetch_assoc($result)) {
        echo '<b>Order ID: </b>' . $row['orderid'] . '<br>';
        echo '<b>Delivery Address: </b>' . $row['deladdress'] . '<br>';
	echo '<b>Order Date: </b>' . $row['dateplaced'] . '<br>';
	echo '<b>Order Time: </b>' . $row['timeplaced'] . '<br>';
	echo '<b>Delivery Time: </b>' . $row['timedelivered'] . '<br>';
	echo '<b>Pickup Order: </b>' . $row['pickuporder'] . '<br>';
	echo '<b>Delivery Rating: </b>' . $row['deliveryrating'] . '<br>';
	echo '<b>Driver ID: </b>' . $row['driverid'] . '<br>';
	echo '<b>Customer ID: </b>' . $row['cusid'] . '<br>';
     }
     mysqli_free_result($result);

// Calculating the total price of the user order
$query = 'SELECT menuitem.dishname, menuitem.price, overallorder.quantity FROM overallorder JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid WHERE orderid = "' . $orderid . '"';
$result=mysqli_query($connection,$query);

echo '<h4>User Order Total Price:</h4>';
while ($row=mysqli_fetch_assoc($result)) {
	echo '<b>Dish Name: </b>' . $row['dishname'] . '<br>';
	echo '<b>Price per Item: </b>$' . $row['price'] . '<br>';
	echo '<b>Quantity: </b>' . $row['quantity'] . '<br>';
	$totalCost = $row['price'] * $row['quantity'];
	echo '<b>Total Cost of Order: </b>$' . $totalCost . '<br>';
     }
     mysqli_free_result($result);

// Disconnects from the database
mysqli_close($connection);
?>

<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
