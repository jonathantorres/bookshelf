-- Ex 1
SELECT `Vendors`.`VendName`,AVG(`Product_Vendors`.`DaysToDeliver`) AS `DeliveryAvg`
FROM `Vendors`
INNER JOIN `Product_Vendors`
  ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
GROUP BY `Vendors`.`VendorID`
ORDER BY `DeliveryAvg`;

-- Ex 2
SELECT `Products`.`ProductName`,SUM(`Order_Details`.`QuotedPrice` * `Order_Details`.`QuantityOrdered`) AS `TotalSales`
FROM `Products`
INNER JOIN `Order_Details`
  ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
GROUP BY `Products`.`ProductNumber`
ORDER BY `Products`.`ProductName`;

-- Ex 3
SELECT `Vendors`.`VendName`,count(`Product_Vendors`.`ProductNumber`) AS `AmountOfProducts`
FROM `Vendors`
INNER JOIN `Product_Vendors`
  ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
GROUP BY `Vendors`.`VendorID`
ORDER BY `Vendors`.`VendName`;

-- Ex 4
SELECT `Vendors`.`VendName`, (
    SELECT count(*)
    FROM `Product_Vendors`
    WHERE `Product_Vendors`.`VendorID` = `Vendors`.`VendorID`
) AS `AmountOfProducts`
FROM `Vendors`
ORDER BY `Vendors`.`VendName`;
