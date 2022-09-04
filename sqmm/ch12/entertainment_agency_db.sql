-- Ex 1
SELECT AVG(`Agents`.`Salary`) AS `AvgSalary`
FROM `Agents`;

-- Ex 2
SELECT `Engagements`.`EngagementNumber`
FROM `Engagements`
WHERE `Engagements`.`ContractPrice` >= (
    SELECT AVG(`Engagements`.`ContractPrice`)
    FROM `Engagements`
);

-- Ex 3
SELECT COUNT(*) AS `Amount`
FROM `Entertainers`
WHERE `Entertainers`.`EntCity` = "Bellevue";
