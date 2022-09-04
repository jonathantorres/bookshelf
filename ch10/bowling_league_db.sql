-- Ex 1 with UNION
SELECT `Tournaments`.`TourneyLocation`, concat(`Bowlers`.`BowlerFirstName`, ' ', `Bowlers`.`BowlerLastName`) AS `BowlerName`, `Bowler_Scores`.`RawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
INNER JOIN `Tourney_Matches`
  ON `Tourney_Matches`.`MatchID` = `Bowler_Scores`.`MatchID`
INNER JOIN `Tournaments`
  ON `Tournaments`.`TourneyID` = `Tourney_Matches`.`TourneyID`
WHERE `Bowler_Scores`.`RawScore` > 165
AND `Tournaments`.`TourneyLocation` = 'Thunderbird Lanes'
UNION
SELECT `Tournaments`.`TourneyLocation`, concat(`Bowlers`.`BowlerFirstName`, ' ', `Bowlers`.`BowlerLastName`) AS `BowlerName`,`Bowler_Scores`.`RawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
INNER JOIN `Tourney_Matches`
  ON `Tourney_Matches`.`MatchID` = `Bowler_Scores`.`MatchID`
INNER JOIN `Tournaments`
  ON `Tournaments`.`TourneyID` = `Tourney_Matches`.`TourneyID`
WHERE `Bowler_Scores`.`RawScore` > 150
AND `Tournaments`.`TourneyLocation` = 'Bolero Lanes';

-- Ex 1 with WHERE
SELECT `Tournaments`.`TourneyLocation`, concat(`Bowlers`.`BowlerFirstName`, ' ', `Bowlers`.`BowlerLastName`) AS `BowlerName`,`Bowler_Scores`.`RawScore`
FROM `Bowlers`
INNER JOIN `Bowler_Scores`
  ON `Bowlers`.`BowlerID` = `Bowler_Scores`.`BowlerID`
INNER JOIN `Tourney_Matches`
  ON `Tourney_Matches`.`MatchID` = `Bowler_Scores`.`MatchID`
INNER JOIN `Tournaments`
  ON `Tournaments`.`TourneyID` = `Tourney_Matches`.`TourneyID`
WHERE (
    `Bowler_Scores`.`RawScore` > 150 AND `Tournaments`.`TourneyLocation` = 'Bolero Lanes'
)
OR (
    `Bowler_Scores`.`RawScore` > 165 AND `Tournaments`.`TourneyLocation` = 'Thunderbird Lanes'
);
