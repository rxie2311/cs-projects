<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 2 | Assignment 3</title>
</head>
<body>

<!-- Include statements -->
<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 2</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Insert a new order into cusorder per user request.</li>
<li>Allow user to pick an existing driver and customer.</li>
<li>Ensure user inputs an order time that takes place before the delivery time.</li>
<li>Allow user to select menu items and quantity.</li>
<li>Display the user order on a separate screen.</li>
</ol>

<!-- Creating user input spaces -->
<form action="generateorder.php" method="post">

<label><b>Input New Order ID:</b></label>
<br>
<input type="text" name="neworderid">

<br>
<br>

<label><b>Input Customer ID:</b></label>
<br>
<input type="text" name="custid">

<br>
<br>

<label><b>Input Driver ID:</b></label>
<br>
<input type="text" name="driveid">

<br>
<br>

<label><b>Input Delivery Address:</b></label>
<br>
<input type="text" name="addr">

<br>
<br>

<label><b>Input Order Date:</b></label>
<br>
<input type="date" name="deldate">

<br>
<br>

<label><b>Input Order Time:</b></label>
<br>
<input type="time" name="ordertime">

<br>
<br>

<label><b>Input Delivery Time:</b></label>
<br>
<input type="time" name="deltime">

<br>
<br>

<label><b>Input Delivery Rating:</b></label>
<br>
<label><input type="number" name="rating" min="1" max="5"> (min: 1, max: 5)</label>

<br>
<br>

<label><b>Input Menu Item ID:</b></label>
<br>
<input type="text" name="dishid">

<br>
<br>

<label><b>Input Item Quantity:</b></label>
<br>
<input type="number" name="dishquantity" min="1">

<br>
<br>

<input type="submit" value="Submit New Order">

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
