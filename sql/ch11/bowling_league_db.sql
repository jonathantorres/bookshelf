-- Ex 1
SELECT `Bowlers`.`BowlerFirstName`,`Bowlers`.`BowlerLastName`,(
    SELECT count(*)
    FROM `Bowler_Scores`
    WHERE `Bowler_Scores`.`BowlerID` = `Bowlers`.`BowlerID`
) AS `GamesCount`
FROM `Bowlers`;

-- Ex 2
SELECT DISTINCT `OuterBowlers`.`BowlerFirstName`,`OuterBowlers`.`BowlerLastName`,`OuterBowlerScores`.`RawScore`
FROM `Bowlers` AS `OuterBowlers`
INNER JOIN `Bowler_Scores` AS `OuterBowlerScores`
  ON `OuterBowlers`.`BowlerID` = `OuterBowlerScores`.`BowlerID`
WHERE `OuterBowlerScores`.`RawScore` < ALL (
    SELECT `Bowler_Scores`.`RawScore`
    FROM `Bowlers`
    INNER JOIN `Bowler_Scores`
      ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
    WHERE `Bowlers`.`TeamID` = `OuterBowlers`.`TeamID`
    AND `OuterBowlers`.`BowlerID` != `Bowlers`.`BowlerID`
);
