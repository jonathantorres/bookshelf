-- Ex 1
SELECT `Agents`.`AgentID`, concat(`Agents`.`AgtFirstName`, ' ', `Agents`.`AgtLastName`) AS `AgtName`
FROM `Agents`
LEFT JOIN `Engagements`
  ON `Agents`.`AgentID` = `Engagements`.`AgentID`
WHERE `Engagements`.`EngagementNumber` IS NULL;

-- Ex 2
SELECT `Customers`.`CustomerID`,`Customers`.`CustFirstName`, `Customers`.`CustLastName`
FROM `Customers`
LEFT JOIN `Engagements`
  ON `Customers`.`CustomerID` = `Engagements`.`CustomerID`
WHERE `Engagements`.`EngagementNumber` IS NULL;

-- Ex 3
SELECT `Entertainers`.`EntStageName`, `Engagements`.`EngagementNumber`, `Engagements`.`StartDate`
FROM `Entertainers`
LEFT JOIN `Engagements`
  ON `Entertainers`.`EntertainerID` = `Engagements`.`EntertainerID`;
