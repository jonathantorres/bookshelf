-- Ex 1
SELECT `ProductNumber`, `WholesalePrice`, `WholesalePrice` - (`WholesalePrice` * .05) AS `ReducedPrice` FROM `Product_Vendors`;

-- Ex 2
SELECT `CustomerID`, `OrderDate`, `OrderNumber` FROM `Orders` ORDER BY `CustomerID` ASC, `OrderDate` DESC;

-- Ex 3
SELECT `VendName`, CONCAT(`VendStreetAddress`, ', ', `VendCity`, ' ', `VendState`, ' ', `VendZipCode`) AS `VendAddress` FROM `Vendors` ORDER BY `VendName`;
