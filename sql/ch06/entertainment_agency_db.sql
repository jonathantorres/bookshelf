-- Ex 1
SELECT `EngagementNumber`, `ContractPrice`,`StartDate`,`EndDate` FROM `Engagements`
WHERE `StartDate` BETWEEN '2012-10-01' AND '2012-10-31'
OR `EndDate` BETWEEN '2012-10-01' AND '2012-10-31';

-- Ex 2
SELECT * FROM `Engagements`
WHERE (
  `StartDate` BETWEEN '2012-10-01' AND '2012-10-31'
  OR `EndDate` BETWEEN '2012-10-01' AND '2012-10-31'
)
AND (`StartTime` BETWEEN '12:00:00' AND '17:00:00');

-- Ex 3
SELECT `EngagementNumber`,`StartDate`,`EndDate` FROM `Engagements` WHERE `StartDate` = `EndDate`;
