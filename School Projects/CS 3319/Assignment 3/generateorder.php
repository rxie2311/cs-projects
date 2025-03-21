<?php
include 'connecttodb.php';
?>

<?php
// Taking user inputs from the text boxes
// Take user inputted order id, customer id and driver id
$uOrderID = $_POST['neworderid'];
$uCusID = $_POST['custid'];
$uDriveID = $_POST['driveid'];

// Take user inputted del address, dateplaced
$uDelAddr = $_POST['addr'];
$uDate = $_POST['deldate'];

// Take user inputted order and delivery hours, mins, sec
$uOrderTime = $_POST['ordertime'];
$uDelTime = $_POST['deltime'];

// Take user inputted delivery rating
$uDelRating = $_POST['rating'];

// Take user inputted dish id and quantity
$uDishID = $_POST['dishid'];
$uQuantity = $_POST['dishquantity'];

// Queries to check if user inputted values are valid
// Check 1: Checking if user inputted order id is non dupe
$query = 'SELECT * FROM cusorder WHERE orderid = "' . $uOrderID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) > 0) {
        die("Error: Order ID already exists. Please enter another Order ID.");
    }

// Check 2: Checking if user inputted cusid and driverid is valid
$query = 'SELECT * FROM customer WHERE cusid = "' . $uCusID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) <= 0) {
        die("Error: Customer ID entered does not exist.");
    }

$query = 'SELECT * FROM driver WHERE driverid = "' . $uDriveID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) <= 0) {
        die("Error: Driver ID entered does not exist.");
    }

// Check 3: Checking if user inputted order time is less than delivery time
list($uOrderHour, $uOrderMin, $uOrderSec) = explode(':', $uOrderTime . ':00');
$totalOrderTime = ($uOrderHour * 3600) + ($uOrderMin * 60) + $uOrderSec;

list($uDelHour, $uDelMin, $uDelSec) = explode(':', $uDelTime . ':00');
$totalDelTime = ($uDelHour * 3600) + ($uDelMin * 60) + $uDelSec;

if ($totalOrderTime >= $totalDelTime) {
	die("Error: Order time must be before delivery time.");
    }

// Check 4: Checking if user inputted menuitemid exists
$query = 'SELECT * FROM menuitem WHERE menuitemid = "' . $uDishID . '"';
$result = mysqli_query($connection,$query);
if (mysqli_num_rows($result) <= 0) {
        die("Error: Menu Item ID entered does not exist.");
    }

// If everything was valid, inserts the user order into cusorder table
$query = 'INSERT INTO cusorder (orderid, deladdress, dateplaced, timeplaced, timedelivered, pickuporder, deliveryrating, driverid, cusid) VALUES ("' . $uOrderID . '", "' . $uDelAddr . '", "' . $uDate . '", "' . $uOrderTime . '", "' . $uDelTime . '", "N", ' . $uDelRating . ', "' . $uDriveID . '", "' . $uCusID . '")';
$result = mysqli_query($connection,$query);
if (!$result) {
        die("Error: Insert query in cusorder error.");
    }

// Inserting the order into overallorder table
$query = 'INSERT INTO overallorder (orderid, menuitemid, quantity) VALUES ("' . $uOrderID . '", "' . $uDishID . '", ' . $uQuantity . ')';
$result = mysqli_query($connection,$query);
if (!$result) {
	die("Error: Insert query in overallorder error.");
    }

// Redirect the user to the new order
header("Location: vieworder.php?orderid=$uOrderID");
exit();

// Close the connection
mysqli_close($connection);
?>
