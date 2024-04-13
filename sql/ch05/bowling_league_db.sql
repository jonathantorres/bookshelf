-- Ex 1
SELECT `TourneyLocation`, `TourneyDate`, `TourneyDate` + INTERVAL 1 YEAR AS `NextYearTourney` FROM `Tournaments` ORDER BY `TourneyLocation`;

-- Ex 2
SELECT CONCAT(`BowlerLastName`, ', ', `BowlerFirstName`) AS `BowlerName`, `BowlerPhoneNumber` FROM `Bowlers` ORDER BY `BowlerName`;

-- Ex 3
SELECT `TeamID`, CONCAT(`BowlerLastName`, ', ', `BowlerFirstName`) AS `BowlerName` FROM `Bowlers` ORDER BY `TeamID`, `BowlerName`;
