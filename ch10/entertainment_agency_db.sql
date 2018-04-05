-- Ex 1
SELECT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `FullName`
FROM `Customers`
UNION
SELECT `Entertainers`.`EntStageName` AS `FullName`
FROM `Entertainers`
ORDER BY `FullName`;

-- Ex 2
SELECT concat(`Customers`.`CustFirstName`, ' ', `CustLastName`) AS `FullName`, 'Customer' AS `Type`
FROM `Customers`
INNER JOIN `Musical_Preferences`
  ON `Customers`.`CustomerID` = `Musical_Preferences`.`CustomerID`
INNER JOIN `Musical_Styles`
  ON `Musical_Styles`.`StyleID` = `Musical_Preferences`.`StyleID`
WHERE `Musical_Styles`.`StyleID` = 10
UNION
SELECT `Entertainers`.`EntStageName`,'Entertainer' AS `Type`
FROM `Entertainers`
INNER JOIN `Entertainer_Styles`
  ON `Entertainer_Styles`.`EntertainerID` = `Entertainers`.`EntertainerID`
INNER JOIN `Musical_Styles`
  ON `Musical_Styles`.`StyleID` = `Entertainer_Styles`.`StyleID`
WHERE `Musical_Styles`.`StyleID` = 10;
