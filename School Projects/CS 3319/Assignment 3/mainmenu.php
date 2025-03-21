<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Main Menu | Assignment 3</title>
</head>
<body>

<!-- PHP that connects the database -->
<?php
include 'connecttodb.php';
?>

<!-- Main text of the website body -->
<h1>Welcome to the Main Menu of Assignment 3</h1>
<h2>Buttons to each task:</h2>

<!-- Radio Buttons to take you to each page -->
<!-- Task 1 Page -->
<form method="get" action="menuitems.php">
    <button type="submit">Task 1: List All Menu Items</button>
</form>

<br>
<br>

<!-- Task 2 Page -->
<form method="get" action="createorder.php">
	<button type="submit">Task 2: User Input Order</button>
</form>

<br>
<br>

<!-- Task 3 Page -->
<form method="get" action="deletemenuitem.php">
	<button type="submit">Task 3: Delete Menu Item</button>
</form>

<br>
<br>

<!-- Task 4 Page -->
<form method="get" action="modifymenuitem.php">
	<button type="submit">Task 4: Modify Menu Item</button>
</form>

<br>
<br>

<!-- Task 5 Page -->
<form method="get" action="nodeliveries.php">
	<button type="submit">Task 5: No Delivery Driver Info</button>
</form>

<br>
<br>

<!-- Task 6 Page -->
<form method="get" action="selectorder.php">
	<button type="submit">Task 6: View Selected Order</button>
</form>

<!-- Disconnect from database -->
<?php
mysqli_close($connection);
?>


</body>
</html>
