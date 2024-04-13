-- Ex 1
SELECT concat(`Agents`.`AgtFirstName`, ' ', `Agents`.`AgtLastName`) AS `AgtName`, `Engagements`.`StartDate`,`Engagements`.`EndDate` FROM `Agents`
INNER JOIN `Engagements`
  ON `Agents`.`AgentID` = `Engagements`.`AgentID`
ORDER BY `Engagements`.`StartDate`;

-- Ex 2
SELECT DISTINCT concat(`Customers`.`CustFirstName`, ' ', `Customers`.`CustLastName`) AS `CustFullName`, `Entertainers`.`EntStageName` FROM `Customers`
INNER JOIN `Engagements`
  ON `Customers`.`CustomerID` = `Engagements`.`CustomerID`
INNER JOIN `Entertainers`
  ON `Engagements`.`EntertainerID` = `Entertainers`.`EntertainerID`;

-- Ex 3
SELECT concat(`Agents`.`AgtFirstName`, ' ', `Agents`.`AgtLastName`) AS `AgtName`, `Entertainers`.`EntStageName`, `Agents`.`AgtZipCode` AS `ZipCode`
FROM `Agents`
INNER JOIN `Entertainers`
  ON `Agents`.`AgtZipCode` = `Entertainers`.`EntZipCode`;
