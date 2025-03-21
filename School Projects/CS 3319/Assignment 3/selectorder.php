<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 6 | Assignment 3</title>
</head>
<body>

<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 6</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Allow the user to select any existing order in the database.</li>
<li>Take them to a detailed page of all of the details of that order.</li>
</ol>

<?php
// Fetch all orders using a query
$query = "SELECT orderid FROM cusorder";
$result = mysqli_query($connection, $query);
if (!$result) {
    die("Error: Query order.");
}

// Label to tell user to select an order
echo "<label><b>Select an Order:</b></label>";
echo "<form method='post' action='viewselectedorder.php'>";

// Display orders as radio buttons
while ($row = mysqli_fetch_assoc($result)) {
    $orderid = $row['orderid'];
    echo "<input type='radio' name='orderid' value='" . $orderid . "' required>";
    echo "<label for='order$orderid'>Order: " . $orderid . "</label><br>";
}

echo "<br>";

// Submit button
echo '<input type="submit" value="View Order">';

echo "</form>";

// Disconnect from database
mysqli_close($connection);
?>

<br>
<br>

<!-- Return to main menu button -->
<form method="get" action="mainmenu.php">
	<button type="submit">Return to Main Menu</button>
</form>


</body>
</html>
