-- Ex 1
SELECT `Entertainers`.`EntertainerID`,`Entertainers`.`EntStageName`
FROM `Entertainers`
WHERE `Entertainers`.`EntertainerID` IN (
    SELECT `E1`.`EntertainerID`
    FROM `Engagements` AS `E1`
    INNER JOIN `Engagements` AS `E2`
      ON `E1`.`EntertainerID` = `E2`.`EntertainerID`
    WHERE `E1`.`EngagementNumber` <> `E2`.`EngagementNumber`
    AND `E1`.`StartDate` <= `E2`.`EndDate`
    AND `E1`.`EndDate` >= `E2`.`StartDate`
    GROUP BY `E1`.`EntertainerID`
    HAVING count(*) > 2
);


-- Ex 2
SELECT `Agents`.`AgtFirstName`,`Agents`.`AgtLastName`,SUM(`Engagements`.`ContractPrice`) AS `ContractsTotal`,SUM(`Engagements`.`ContractPrice` * `Agents`.`CommissionRate`) AS `AgentCommission`
FROM `Agents`
INNER JOIN `Engagements`
  ON `Engagements`.`AgentID` = `Agents`.`AgentID`
GROUP BY `Agents`.`AgentID`
HAVING `AgentCommission` > 1000;
