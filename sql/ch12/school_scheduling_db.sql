-- Ex 1
SELECT AVG(`Classes`.`Duration`) AS `AvgDuration`
FROM `Classes`;

-- Ex 2
SELECT `Staff`.`StfLastname`,`Staff`.`StfFirstName`
FROM `Staff`
WHERE `Staff`.`DateHired` = (
    SELECT MIN(`Staff`.`DateHired`)
    FROM `Staff`
);

-- Ex 3
SELECT COUNT(*) AS `Total`
FROM `Classes`
WHERE `Classes`.`ClassRoomID` = 3346;
