-- Ex 1
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustFullName`,`OrdersWithHelmets`.`ProductName`
FROM `Customers`
LEFT JOIN (
    SELECT `Orders`.`OrderNumber`, `Orders`.`CustomerID`, `Products`.`ProductName`
    FROM `Orders`
    INNER JOIN `Order_Details`
      ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
    INNER JOIN `Products`
      ON `Order_Details`.`ProductNumber` = `Products`.`ProductNumber`
    WHERE `Products`.`ProductName` LIKE "%Helmet"
) AS `OrdersWithHelmets`
  ON `Customers`.`CustomerID` = `OrdersWithHelmets`.`CustomerID`
WHERE `OrdersWithHelmets`.`ProductName` IS NULL;

-- Ex 2
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustFullName`, `Employees`.`EmployeeID`
FROM `Customers`
LEFT JOIN `Employees`
  ON `Customers`.`CustZipCode` = `Employees`.`EmpZipCode`
WHERE `Employees`.`EmployeeID` IS NULL;

-- Ex 3
SELECT DISTINCT `Products`.`ProductNumber`,`Products`.`ProductName`,`Orders`.`OrderDate`
FROM `Products`
LEFT JOIN `Order_Details`
  ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
LEFT JOIN `Orders`
  ON `Order_Details`.`OrderNumber` = `Orders`.`OrderNumber`;
