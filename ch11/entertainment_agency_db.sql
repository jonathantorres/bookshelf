-- Ex 1
SELECT `Entertainers`.`EntStageName`,(
    SELECT count(`Engagements`.`EngagementNumber`)
    FROM `Engagements`
    WHERE `Engagements`.`EntertainerID` = `Entertainers`.`EntertainerID`
) AS `EngagementAmount`
FROM `Entertainers`;

-- Ex 2
SELECT `Customers`.`CustFirstName`,`Customers`.`CustLastName`
FROM `Customers`
WHERE `Customers`.`CustomerID` IN(
    SELECT DISTINCT `Engagements`.`CustomerID`
    FROM `Engagements`
    INNER JOIN `Entertainers`
      ON `Engagements`.`EntertainerID` = `Entertainers`.`EntertainerID`
    INNER JOIN `Entertainer_Styles`
      ON `Entertainer_Styles`.`EntertainerID` = `Entertainers`.`EntertainerID`
    WHERE `Entertainer_Styles`.`StyleID` IN(6,11)
);

-- Ex 3
SELECT `Entertainers`.`EntStageName`
FROM `Entertainers`
WHERE `Entertainers`.`EntertainerID` IN(
    SELECT DISTINCT `Engagements`.`EntertainerID`
    FROM `Engagements`
    INNER JOIN `Customers`
      ON `Engagements`.`CustomerID` = `Customers`.`CustomerID`
    WHERE `Customers`.`CustLastName` IN('Berg','Hallmark')
);

-- Ex 4
SELECT `Agents`.`AgtFirstName`,`Agents`.`AgtLastName`
FROM `Agents`
WHERE `Agents`.`AgentID` NOT IN(
    SELECT DISTINCT `Agents`.`AgentID`
    FROM `Agents`
    INNER JOIN `Engagements`
      ON `Agents`.`AgentID` = `Engagements`.`AgentID`
);
