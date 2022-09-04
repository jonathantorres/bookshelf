-- Ex 1
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustName`,
`Orders`.`OrderDate`
FROM `Customers`
INNER JOIN `Orders`
  ON `Customers`.`CustomerID` = `Orders`.`CustomerID`
ORDER BY `Orders`.`OrderDate`;


-- Ex 2
SELECT DISTINCT concat(`Employees`.`EmpFirstName`, ' ', `Employees`.`EmpLastName`) AS `EmpFullName`,concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustFullName`
FROM `Employees`
INNER JOIN `Orders`
  ON `Employees`.`EmployeeID` = `Orders`.`EmployeeID`
INNER JOIN `Customers`
  ON `Orders`.`CustomerID` = `Customers`.`CustomerID`;


-- Ex 3
SELECT `Orders`.`OrderNumber`,`Orders`.`OrderDate`,`Products`.`ProductNumber`,`Products`.`ProductName`,`Order_Details`.`QuotedPrice`,`Order_Details`.`QuantityOrdered`,
(`Order_Details`.`QuotedPrice` * `Order_Details`.`QuantityOrdered`) AS `AmountOwed`
FROM `Orders`
INNER JOIN `Order_Details`
  ON `Orders`.`OrderNumber` = `Order_Details`.`OrderNumber`
INNER JOIN `Products`
  ON `Order_Details`.`ProductNumber` = `Products`.`ProductNumber`
ORDER BY `Orders`.`OrderNumber`;


-- Ex 4
SELECT `Vendors`.`VendName`,`Products`.`ProductName`,`Product_Vendors`.`WholesalePrice` FROM `Vendors`
INNER JOIN `Product_Vendors`
  ON `Vendors`.`VendorID` = `Product_Vendors`.`VendorID`
INNER JOIN `Products`
  ON `Product_Vendors`.`ProductNumber` = `Products`.`ProductNumber`
WHERE `Product_Vendors`.`WholesalePrice` <= 100;


-- Ex 5
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustName`,
concat(`Employees`.`EmpFirstName`, ' ', `Employees`.`EmpLastName`) AS `EmpName`
FROM `Customers`
INNER JOIN `Employees`
  ON `Customers`.`CustLastName` = `Employees`.`EmpLastName`;


-- Ex 6
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustName`,
concat(`Employees`.`EmpFirstName`, ' ', `Employees`.`EmpLastName`) AS `EmpName`, `Employees`.`EmpCity` AS `City`
FROM `Customers`
INNER JOIN `Employees`
  ON `Customers`.`CustCity` = `Employees`.`EmpCity`;
