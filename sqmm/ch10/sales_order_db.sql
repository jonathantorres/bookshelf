-- Ex 1
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustName`,`Products`.`ProductName`, 'Customer' AS `RowID`
FROM `Customers`
INNER JOIN `Orders`
  ON `Orders`.`CustomerID` = `Customers`.`CustomerID`
INNER JOIN `Order_Details`
  ON `Order_Details`.`OrderNumber`= `Orders`.`OrderNumber`
INNER JOIN `Products`
  ON `Products`.`ProductNumber` = `Order_Details`.`ProductNumber`
WHERE `Products`.`ProductName` LIKE "%helmet%"
UNION
SELECT `Vendors`.`VendName`,`Products`.`ProductName`,'Vendor' AS `RowID`
FROM `Vendors`
INNER JOIN `Product_Vendors`
  ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
INNER JOIN `Products`
  ON `Products`.`ProductNumber` = `Product_Vendors`.`ProductNumber`
WHERE `Products`.`ProductName` LIKE "%helmet%";
