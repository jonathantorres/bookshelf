-- Ex 1
SELECT AVG(`Products`.`RetailPrice`) AS `AvgRetailPrice`
FROM `Products`
WHERE `Products`.`CategoryID` = 2;

-- Ex 2
SELECT MAX(`Orders`.`OrderDate`) AS `MostRecentOrder`
FROM `Orders`;

-- Ex 3
SELECT SUM(`Order_Details`.`QuotedPrice` * `Order_Details`.`QuantityOrdered`) AS `TotalAmount`
FROM `Orders`
INNER JOIN `Order_Details`
  ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
WHERE `Orders`.`OrderNumber` = 8;
