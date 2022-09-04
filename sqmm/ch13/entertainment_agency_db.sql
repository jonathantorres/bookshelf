-- Ex 1
SELECT `Agents`.`AgtFirstName`,`Agents`.`AgtLastName`, SUM(`Engagements`.`ContractPrice`) AS `EngagementSales`, (SUM(`Engagements`.`ContractPrice`) * `Agents`.`CommissionRate`) AS `AgentCommission`
FROM `Agents`
INNER JOIN `Engagements`
  ON `Agents`.`AgentID` = `Engagements`.`AgentID`
GROUP BY `Agents`.`AgentID`
ORDER BY `Agents`.`AgtFirstName`,`Agents`.`AgtLastName`;
