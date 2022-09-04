-- Ex 1
SELECT * FROM `Tournaments` WHERE `TourneyDate` BETWEEN '2012-09-01' AND '2012-09-31';

-- Ex 2
SELECT * FROM `Tournaments` WHERE `TourneyLocation` IN('Bolero Lanes','Red Rooster Lanes','Thunderbird Lanes') ORDER BY `TourneyLocation`;

-- Ex 3
SELECT * FROM `Bowlers`
WHERE `BowlerCity` IN('Bellevue','Bothell','Duvall','Redmond','Woodinville')
AND `TeamId` BETWEEN 5 AND 8;
