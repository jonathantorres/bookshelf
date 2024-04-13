-- Ex 1
SELECT `Teams`.`TeamID`,`Bowlers`.`BowlerID`,`Bowlers`.`BowlerFirstName`,`Bowlers`.`BowlerLastName`, max(`Bowler_Scores`.`RawScore`) AS `MaxScore`
FROM `Teams`
INNER JOIN `Bowlers`
  ON `Teams`.`CaptainID` = `Bowlers`.`BowlerID`
INNER JOIN `Bowler_Scores`
  ON `Bowler_Scores`.`BowlerID` = `Bowlers`.`BowlerID`
GROUP BY `Teams`.`TeamID`
HAVING `MaxScore` > (
    SELECT max(`BS1`.`RawScore`)
    FROM `Teams` AS `T1`
    INNER JOIN `Bowlers` AS `B1`
      ON `T1`.`TeamID` = `B1`.`TeamID`
    INNER JOIN `Bowler_Scores` AS `BS1`
      ON `B1`.`BowlerID` = `BS1`.`BowlerID`
    WHERE `T1`.`TeamID` = `Teams`.`TeamID`
    AND `B1`.`BowlerID` <> `Bowlers`.`BowlerID`
);

-- Ex 2
SELECT `Bowlers`.`BowlerFirstName`,`Bowlers`.`BowlerLastName`, AVG(`Bowler_Scores`.`RawScore`) AS `AvgRawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
GROUP BY `Bowlers`.`BowlerID`
HAVING `AvgRawScore` > 155;

-- Ex 3
SELECT `Bowlers`.`BowlerLastName`,`Bowlers`.`BowlerFirstName`, AVG(`Bowler_Scores`.`RawScore`) AS `AvgRawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
GROUP BY `Bowlers`.`BowlerID`
HAVING `AvgRawScore` >= (
    SELECT AVG(`BS1`.`RawScore`)
    FROM `Bowlers` AS `B1`
    INNER JOIN `Bowler_Scores` AS `BS1`
      ON `B1`.`BowlerID` = `BS1`.`BowlerID`
)
ORDER BY `Bowlers`.`BowlerLastName`;
