<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Task 1 | Assignment 3</title>
</head>
<body>

<!-- Include statements -->
<?php
include 'connecttodb.php';
?>

<!-- Body of the webpage -->
<h1>Welcome to Task 1</h1>

<!-- Listing out the description of this task -->
<h2>Goals of this task:</h2>
<ol>
<li>Neatly list all items in the menuitems table.</li>
<li>Allow the user to order the items by dishname or price.</li>
<li>Allow the user to order the items in ascending or descending order.</li>
</ol>

<!-- Radio button to let the user choose what to sort by -->
<form action="getmenuitems.php"  method="post">

<label><b>Sort by Attribute:</b></label>
<br>
<label><input type="radio" name="attribute" value="dishname">Dish Name</label>
<br>
<label><input type="radio" name="attribute" value="price">Price</label>

<br>
<br>

<label><b>Order in:</b></label>
<br>
<label><input type="radio" name="order" value="ASC">Ascending Order</label>
<br>
<label><input type="radio" name="order" value="DESC">Descending Order</label>

<br>
<br>

<input type="submit" value="Submit Sort Options">

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
