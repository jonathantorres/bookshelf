-- Ex 1
SELECT `Teams`.`TeamName`,concat(`Bowlers`.`BowlerFirstName`, ' ', `Bowlers`.`BowlerLastName`) AS `BowlerName` FROM `Teams`
INNER JOIN `Bowlers`
  ON `Teams`.`TeamID` = `Bowlers`.`TeamID`;

-- Ex 2
SELECT `Bowler_Scores`.`MatchID`,`Teams`.`TeamName`,concat(`Bowlers`.`BowlerFirstName`, ' ', `Bowlers`.`BowlerLastName`) AS `BowlerName`,`Bowler_Scores`.`GameNumber`,`Bowler_Scores`.`RawScore`
FROM `Bowlers`
INNER JOIN `Teams`
  ON `Teams`.`TeamID` = `Bowlers`.`TeamID`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`;

-- Ex 3
SELECT concat(`Bowlers1`.`BowlerFirstName`, ' ', `Bowlers1`.`BowlerLastName`) AS `FirstBowler`, `Bowlers1`.`BowlerZip`,concat(`Bowlers2`.`BowlerFirstName`, ' ', `Bowlers2`.`BowlerLastName`) AS `SecondBowler`
FROM `Bowlers` AS `Bowlers1`
INNER JOIN `Bowlers` AS `Bowlers2`
  ON (
    `Bowlers1`.`BowlerZip` = `Bowlers2`.`BowlerZip`
    AND concat(`Bowlers1`.`BowlerFirstName`, ' ', `Bowlers1`.`BowlerLastName`) != concat(`Bowlers2`.`BowlerFirstName`, ' ', `Bowlers2`.`BowlerLastName`)
  );
