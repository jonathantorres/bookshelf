-- Ex 1
SELECT `Categories`.`CategoryDescription`, count(`Classes`.`ClassID`) AS `ClassCount`
FROM `Categories`
INNER JOIN `Subjects`
  ON `Categories`.`CategoryID` = `Subjects`.`CategoryID`
INNER JOIN `Classes`
  ON `Classes`.`SubjectID` = `Subjects`.`SubjectID`
GROUP BY `Categories`.`CategoryID`
ORDER BY `Categories`.`CategoryDescription`;

-- Ex 2
SELECT `Staff`.`StfFirstName`,`Staff`.`StfLastname`,count(`Faculty_Classes`.`ClassID`) AS `ClassesToTeach`
FROM `Staff`
INNER JOIN `Faculty_Classes`
  ON `Staff`.`StaffID` = `Faculty_Classes`.`StaffID`
GROUP BY `Staff`.`StaffID`
ORDER BY `Staff`.`StfFirstName`,`Staff`.`StfLastname`;

-- Ex 3
SELECT `Staff`.`StfFirstName`,`Staff`.`StfLastname`,(
    SELECT count(*)
    FROM `Faculty_Classes`
    WHERE `Faculty_Classes`.`StaffID` = `Staff`.`StaffID`
) AS `ClassesToTeach`
FROM `Staff`
ORDER BY `Staff`.`StfFirstName`,`Staff`.`StfLastname`;
