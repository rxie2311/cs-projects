-- ---------------------------------
-- SCRIPT 2

-- Use Statement
USE assign2db;


-- Part 1 SQL Updates
SELECT * FROM menuitem;
UPDATE menuitem SET dishname = 'Pasta alla Norma', veggie = 'Y' WHERE dishname = 'Pasta alla Brenda';

SELECT * FROM cusorder;
UPDATE cusorder SET deliveryrating = 3 WHERE driverid IN (SELECT driverid FROM driver WHERE firstname = 'Marge');

SELECT * FROM menuitem;
SELECT * FROM cusorder;


-- Part 2 SQL Inserts
SELECT * FROM customer;
INSERT INTO customer VALUES ('CFQ1', 'Walter', 'White', '9847652045');

SELECT * FROM driver;
INSERT INTO driver VALUES ('D777', 'Jesse', 'Pinkman', '9438343283');

SELECT * FROM menuitem;
INSERT INTO menuitem VALUES ('MIII', 'Mapo Tofu', 15.45, 241, 'N');

SELECT * FROM cusorder;
INSERT INTO cusorder VALUES ('C166', '420 Main Street', '2025-01-09', '18:00:00', '19:00:00', 'N', 5, 'D777', 'CFQ1');

SELECT * FROM overallorder;
INSERT INTO overallorder VALUES ('C166', 'MIII', 3);

SELECT * FROM customer;
SELECT * FROM driver;
SELECT * FROM menuitem;
SELECT * FROM cusorder;
SELECT * FROM overallorder;


-- Part 3 SQL Queries
-- Query 1
SELECT lastname FROM driver;


-- Query 2
SELECT DISTINCT lastname FROM driver;


-- Query 3
SELECT * FROM menuitem ORDER BY caloriecount;


-- Query 4
SELECT dishname, caloriecount, price FROM menuitem WHERE veggie = 'Y' ORDER BY price;


-- Query 5
SELECT orderid, deladdress, deliveryrating FROM cusorder WHERE driverid IN (SELECT driverid FROM driver WHERE lastname = 'Simpson');


-- Query 6
SELECT driver.firstname, driver.lastname FROM driver LEFT JOIN cusorder ON cusorder.driverid = driver.driverid WHERE cusorder.driverid IS NULL;


-- Query 7
SELECT customer.firstname, customer.lastname, cusorder.orderid, cusorder.dateplaced, driver.firstname, driver.lastname FROM cusorder JOIN customer ON cusorder.cusid = customer.cusid LEFT JOIN driver ON cusorder.driverid = driver.driverid;


-- Query 8
SELECT cusorder.orderid, cusorder.dateplaced, menuitem.dishname, menuitem.price, overallorder.quantity FROM overallorder JOIN cusorder ON overallorder.orderid = cusorder.orderid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid ORDER BY overallorder.orderid;


-- Query 9
-- First table counts all deliveries made by each driver by joining it with cusorder
SELECT driver.firstname, driver.lastname, COUNT(cusorder.orderid) AS deliveries FROM driver LEFT JOIN cusorder ON driver.driverid = cusorder.driverid GROUP BY driver.driverid

-- Union to join first and second tables together into one table
UNION

-- Second table uses query 6 to save 0 to all drivers without any deliveries
SELECT driver.firstname, driver.lastname, 0 AS deliveries FROM driver LEFT JOIN cusorder ON cusorder.driverid = driver.driverid WHERE cusorder.driverid IS NULL

-- Ordering the table by delivery count
ORDER BY deliveries;


-- Query 10
-- Displaying orderid, dishname, quantity as well as the formatted prices
SELECT overallorder.orderid, menuitem.dishname, overallorder.quantity, CONCAT('$', FORMAT(menuitem.price, 2)) AS "Cost Of One Item", CONCAT('$', FORMAT(menuitem.price * overallorder.quantity, 2)) AS "Total Cost For This Item"

-- Joining cusorder and menuitem tables to overallorder to look for matching orderid and menuitemid
FROM overallorder JOIN cusorder ON overallorder.orderid = cusorder.orderid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid

-- Condition is it will only output the delivery addresses that are 20 Main Street
WHERE cusorder.deladdress = '20 Main Street'

-- Ordering by orderid
ORDER BY overallorder.orderid;


-- Query 11
-- Displaying first and last name, orderid and dishname
SELECT customer.firstname, customer.lastname, overallorder.orderid, menuitem.dishname

-- Joining customer, cusorder and menuitem tables to overallorder to look for matching cusid and menuitemid
FROM overallorder JOIN cusorder ON overallorder.orderid = cusorder.orderid JOIN customer ON cusorder.cusid = customer.cusid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid

-- Condition is it will only output vegetarian dishes
WHERE menuitem.veggie = 'Y';


-- Query 12
-- For testing purposes, these statements will drop the views below if they already exist
DROP VIEW IF EXISTS OrderTotals;
DROP VIEW IF EXISTS HighestTotal;

-- Creating a view of totals spent on orders for all customers
CREATE VIEW OrderTotals AS SELECT cusorder.cusid AS cid, cusorder.orderid AS oid, SUM(menuitem.price * overallorder.quantity) AS total

-- Joining overallorder and menuitem tables to cusorder to find matching orderid and menuitemid for the order
FROM cusorder JOIN overallorder ON cusorder.orderid = overallorder.orderid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid

-- Grouping the view by customerid and orderid
GROUP BY cusorder.cusid, cusorder.orderid;

-- Creating a second view to find the highest total spent on a single order
CREATE VIEW HighestTotal AS SELECT MAX(total) AS hightotal FROM OrderTotals;

-- Joining the views together with each other and with customer to output firstname, lastname and highest spent total
SELECT customer.firstname, customer.lastname, HighestTotal.hightotal FROM customer JOIN OrderTotals ON customer.cusid = OrderTotals.cid JOIN HighestTotal ON OrderTotals.total = HighestTotal.hightotal;


-- Query 13
-- Returning firstname and lastname of drivers
SELECT driver.firstname, driver.lastname

-- Joining cusorder, overallorder and menuitem with driver table to find all drivers who have delivered food
FROM driver JOIN cusorder ON driver.driverid = cusorder.driverid JOIN overallorder ON cusorder.orderid = overallorder.orderid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid

-- Condition is that the driver must never have delivered Beef Lasagna before
-- The second SELECT statement is creating a table of drivers who have delivered Beef Lasagna so the table can exclude them
WHERE driver.driverid NOT IN (SELECT DISTINCT cusorder.driverid FROM cusorder JOIN overallorder ON cusorder.orderid = overallorder.orderid JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid WHERE menuitem.dishname = 'Beef Lasagna')

-- Union to join first and second tables together into one table
UNION

-- Second table uses query 6 to save all drivers without any deliveries
SELECT driver.firstname, driver.lastname FROM driver LEFT JOIN cusorder ON cusorder.driverid = driver.driverid WHERE cusorder.driverid IS NULL;


-- Query 14
-- Returning dishname, menuitemid, the distinct number of orders (if the dish appears multiple times in the same order, only counts as 1)
-- and the total quantity ordered of that dish
SELECT menuitem.dishname, menuitem.menuitemid, COUNT(DISTINCT overallorder.orderid) as total_no_orders, SUM(overallorder.quantity) as total_quantity

-- Joining overallorder and menuitem together to access dishname
FROM overallorder JOIN menuitem ON overallorder.menuitemid = menuitem.menuitemid

-- Group the table by the dishname and menuitemid to sort order number and quantity of each dish
GROUP BY menuitem.menuitemid, menuitem.dishname

-- Having statement to check if the dish has been cooked more than 6 times in total (6 or more quantity)
HAVING total_quantity >= 6

-- Sorting the dishes by dish quantity
ORDER BY total_quantity;


-- Query 15 - MY QUERY
-- Q: Display all of the firstnames of drivers that have a delivery rating of 3 or more in alphabetical order
SELECT DISTINCT driver.firstname FROM driver JOIN cusorder ON driver.driverid = cusorder.driverid WHERE cusorder.deliveryrating >= 3 ORDER BY driver.firstname;


-- Part 4 SQL Views/Deletes
-- For testing purposes, these statements will drop the view if it already exists
DROP VIEW IF EXISTS MyView;

-- Showing driverid, firstname, lastname, rating, orderid, time order was placed, time order was delivered
CREATE VIEW MyView AS SELECT driver.driverid, driver.firstname, driver.lastname, cusorder.deliveryrating, cusorder.orderid, cusorder.timeplaced, cusorder.timedelivered FROM driver JOIN cusorder ON driver.driverid = cusorder.driverid;

-- Selecting all orders delivered within an hour in the view
-- Uses TIMESTAMPDIFF to check for the difference in minutes to make sure it is less than or equal to 60
SELECT * FROM MyView WHERE TIMESTAMPDIFF(MINUTE, timeplaced, timedelivered) <= 60;

-- Showing all rows and columns of driver table
SELECT * FROM driver;

-- Deleting driverid D666
DELETE FROM driver WHERE driverid = 'D666';

-- Proving the driver was deleted
SELECT * FROM driver;

-- Query to count the number of drivers (rows) from driver
SELECT COUNT(*) FROM driver;

-- Deleting driverid D333
DELETE FROM driver WHERE driverid = 'D333';

-- Showing the driver count again to prove that D333 was deleted
SELECT COUNT(*) FROM driver;

-- D666 was deleted because there was no foreign key value referencing it in other tables.
-- D333 could not be deleted because there was a foreign key that had it as the value in cusorder.