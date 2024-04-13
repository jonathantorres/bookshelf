-- Ex 1
SELECT `Products`.`ProductName`, (
    SELECT MAX(`Orders`.`OrderDate`) AS `LastPurchaseDate`
    FROM `Orders`
    INNER JOIN `Order_Details`
      ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
    WHERE `Order_Details`.`ProductNumber` = `Products`.`ProductNumber`
) AS `LastPurchaseDate`
FROM `Products`;

-- Ex 2
SELECT `Customers`.`CustFirstName`,`Customers`.`CustLastName` FROM `Customers`
WHERE `Customers`.`CustomerID` IN(
    SELECT DISTINCT `Orders`.`CustomerID`
    FROM `Orders`
    INNER JOIN `Order_Details`
      ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
    INNER JOIN `Products`
      ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
    WHERE `Products`.`CategoryID` = 2
);

-- Ex 3
SELECT `Products`.`ProductName`
FROM `Products`
WHERE `Products`.`ProductNumber` NOT IN(
    SELECT `Products`.`ProductNumber`
    FROM `Products`
    INNER JOIN `Order_Details`
      ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
);
