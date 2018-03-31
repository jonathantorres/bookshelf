-- Ex 1
SELECT `Tourney_Matches`.`MatchID`,`Tourney_Matches`.`TourneyID`,`OddLaneTeams`.`TeamName` AS `OddLaneTeam`,`EvenLaneTeams`.`TeamName`
FROM `Tourney_Matches`
LEFT JOIN `Match_Games`
ON  `Match_Games`.`MatchID` = `Tourney_Matches`.`MatchID`
LEFT JOIN `Teams` AS `OddLaneTeams`
  ON `OddLaneTeams`.`TeamID` = `Tourney_Matches`.`OddLaneTeamID`
LEFT JOIN `Teams` AS `EvenLaneTeams`
  ON `EvenLaneTeams`.`TeamID` = `Tourney_Matches`.`EvenLaneTeamID`
WHERE `Match_Games`.`MatchID` IS NULL;

-- Ex 2
SELECT `Tournaments`.*, `Match_Games`.`MatchID`,`Match_Games`.`GameNumber`,`Teams`.`TeamName`
FROM `Tournaments`
LEFT JOIN `Tourney_Matches`
  ON `Tournaments`.`TourneyID` = `Tourney_Matches`.`TourneyID`
LEFT JOIN `Match_Games`
  ON `Match_Games`.`MatchID` = `Tourney_Matches`.`MatchID`
LEFT JOIN `Teams`
  ON `Teams`.`TeamID` = `Match_Games`.`WinningTeamID`;
