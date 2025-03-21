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
$orderid = $_POST['orderid'];

// Query to join all relevant information into one big table
$query = 'SELECT co.orderid, co.deladdress, co.dateplaced, co.timeplaced, co.timedelivered, co.pickuporder, co.deliveryrating, d.firstname AS driver_fname, d.lastname AS driver_lname, c.firstname AS customer_fname, c.lastname AS customer_lname, m.dishname, m.price, oo.quantity FROM cusorder AS co JOIN driver AS d ON co.driverid = d.driverid JOIN customer AS c ON co.cusid = c.cusid JOIN overallorder AS oo ON co.orderid = oo.orderid JOIN menuitem AS m ON oo.menuitemid = m.menuitemid WHERE co.orderid = "' . $orderid . '"';
$result = mysqli_query($connection,$query);
if (!$result) {
         die("database query failed.");
}

// Printing out all of the details of the order
$row = mysqli_fetch_assoc($result);
// Printing out the order details
echo '<h1>Order Details</h1>';
echo '<h3>Order ID: ' . $row['orderid'] . '</h3>';
echo '<b>Order Date: </b>' . $row['dateplaced'] . '<br>';
echo '<b>Order Time: </b>' . $row['timeplaced'] . '<br>';

// Printing out delivery details
echo '<h3>Delivery Details:</h3>';
echo '<b>Pickup: </b>' . $row['pickuporder'] . '<br>';
echo '<b>Delivery Time: </b>' . $row['timedelivered'] . '<br>';
echo '<b>Delivery Address: </b>' . $row['deladdress'] . '<br>';
echo '<b>Delivery Rating: </b>' . $row['deliveryrating'] . '<br>';

// Printing out driver details
echo '<h3>Driver Details:</h3>';
echo '<b>Driver Name: </b>' . $row['driver_fname'] . ' ' . $row['driver_lname'] . '<br>';

// Printing out customer details
echo '<h3>Customer Details:</h3>';
echo '<b>Customer Name: </b>' . $row['customer_fname'] . ' ' . $row['customer_lname'] . '<br>';

// Printing out order items
$query = 'SELECT co.orderid, co.deladdress, co.dateplaced, co.timeplaced, co.timedelivered, co.pickuporder, co.deliveryrating, d.firstname AS driver_fname, d.lastname AS driver_lname, c.firstname AS customer_fname, c.lastname AS customer_lname, m.dishname, m.price, oo.quantity FROM cusorder AS co JOIN driver AS d ON co.driverid = d.driverid JOIN customer AS c ON co.cusid = c.cusid JOIN overallorder AS oo ON co.orderid = oo.orderid JOIN menuitem AS m ON oo.menuitemid = m.menuitemid WHERE co.orderid = "' . $orderid . '"';
$result = mysqli_query($connection,$query);

echo '<h3>Ordered Items:</h3>';
$totalPrice = 0;
while ($oRow=mysqli_fetch_assoc($result)) {
	echo '<b>Dish Name: </b>' . $oRow['dishname'] . '<br>';
	echo '<b>Price: </b>$' . $oRow['price'] . ' x' . $oRow['quantity'] . '<br><br>';
	$totalPrice = $totalPrice + ($oRow['price'] * $oRow['quantity']);
}
mysqli_free_result($result);
echo '<b>Total Order Cost: </b>$' . $totalPrice . '<br>';

// Closing connection to database
mysqli_close($connection);
?>

<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
