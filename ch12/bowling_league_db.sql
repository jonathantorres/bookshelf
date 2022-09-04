-- Ex 1
SELECT MAX(
    round(
        (
            (200 - round(
                (SELECT AVG(`bowler_scores`.`RawScore`)
                 FROM `bowler_scores`
                 WHERE `bowler_scores`.`BowlerID` = `bowlers`.`BowlerID`), 0
            )) * 0.9
        ),0
    )
) AS `HighHandicap`
FROM `bowlers`;

-- Ex 2
SELECT `Tournaments`.`TourneyLocation`
FROM `Tournaments`
WHERE `Tournaments`.`TourneyDate` = (
    SELECT MIN(`Tournaments`.`TourneyDate`)
    FROM `Tournaments`
);

-- Ex 3
SELECT MAX(`Tournaments`.`TourneyDate`) AS `TourneyDate`
FROM `Tournaments`;
