-- Ex 1
SELECT `VendName`, `VendCity` FROM `Vendors` WHERE `VendCity` IN('Ballard','Bellevue','Redmond');

-- Ex 2
SELECT `ProductName`, `RetailPrice` FROM `Products` WHERE `RetailPrice` >= 125.00 ORDER BY `ProductName`;

-- Ex 3
SELECT `VendName`,`VendWebPage` FROM `Vendors` WHERE `VendWebPage` IS NULL ORDER BY `VendName`;
