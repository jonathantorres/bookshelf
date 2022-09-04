-- Ex 1
SELECT `Vendors`.`VendName`, AVG(`Product_Vendors`.`DaysToDeliver`) AS `DayAvg`
FROM `Vendors`
INNER JOIN `Product_Vendors`
  ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
GROUP BY `Vendors`.`VendorID`
HAVING `DayAvg` > (
    SELECT AVG(`Product_Vendors`.`DaysToDeliver`)
    FROM `Vendors`
    INNER JOIN `Product_Vendors`
      ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
);


-- Ex 2
SELECT `Products`.`ProductName`, SUM(`Order_Details`.`QuotedPrice` * `Order_Details`.`QuantityOrdered`) AS `TotalSales`, `Products`.`CategoryID`
FROM `Products`
INNER JOIN `Categories`
  ON `Categories`.`CategoryID` = `Products`.`CategoryID`
INNER JOIN `Order_Details`
  ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
GROUP BY `Products`.`ProductNumber`
HAVING `TotalSales` > (
    SELECT AVG(`S`.`SumCategory`)
    FROM `ch14_order_totals` AS `S`
    WHERE `S`.`CategoryID` = `Products`.`CategoryID`
    GROUP BY `S`.`CategoryID`
);


-- Ex 3
SELECT count(*) AS `OrderCount`
FROM (
    SELECT count(`Products`.`ProductNumber`) AS `ProductCount`
    FROM `Orders`
    INNER JOIN `Order_Details`
      ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
    INNER JOIN `Products`
      ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
    GROUP BY `Orders`.`OrderNumber`
    HAVING `ProductCount` = 1
) AS `OrdersWithOneProduct`;
