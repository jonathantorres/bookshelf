-- Ex 1
SELECT `Bowlers`.`BowlerLastName`,`Bowlers`.`BowlerFirstName`, AVG(`Bowler_Scores`.`RawScore`) AS `AvgRawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
GROUP BY `Bowlers`.`BowlerID`;

-- Ex 2
SELECT
   `Bowler_Scores`.`BowlerID` AS `BowlerID`,
   `Bowlers`.`BowlerLastName` AS `BowlerLastName`,
   `Bowlers`.`BowlerFirstName` AS `BowlerFirstName`,
   sum(`Bowler_Scores`.`RawScore`) AS `TotalPins`,
   count(`Bowler_Scores`.`RawScore`) AS `GamesBowled`,
   round(avg(`Bowler_Scores`.`RawScore`),0) AS `CurAvg`,
   round((0.9 * (200 - round(avg(`Bowler_Scores`.`RawScore`),0))),0) AS `CurHcp`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
GROUP BY `Bowler_Scores`.`BowlerID`,`Bowlers`.`BowlerLastName`,`Bowlers`.`BowlerFirstName`;

-- Ex 3
SELECT `Bowlers`.`BowlerLastName`,`Bowlers`.`BowlerFirstName`,(
    SELECT max(`Bowler_Scores`.`RawScore`)
    FROM `Bowler_Scores`
    WHERE `Bowler_Scores`.`BowlerID` = `Bowlers`.`BowlerID`
) AS `HighestScore`
FROM `Bowlers`;
