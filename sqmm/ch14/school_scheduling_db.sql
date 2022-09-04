-- Ex 1
SELECT `Categories`.`CategoryDescription`, count(`Classes`.`ClassID`) AS `ClassAmount`
FROM `Categories`
INNER JOIN `Subjects`
  ON `Categories`.`CategoryID` = `Subjects`.`CategoryID`
INNER JOIN `Classes`
  ON `Classes`.`SubjectID` = `Subjects`.`SubjectID`
GROUP BY `Categories`.`CategoryID`
HAVING `ClassAmount` >= 3;

-- Ex 2
SELECT `Staff`.`StfFirstName`,`Staff`.`StfLastname`,count(`Faculty_Classes`.`StaffID`) AS `ClassesAmount`
FROM `Staff`
LEFT JOIN `Faculty_Classes`
  ON `Faculty_Classes`.`StaffID` = `Staff`.`StaffID`
GROUP BY `Staff`.`StaffID`
HAVING `ClassesAmount` < 3;

-- Ex 3
SELECT `Categories`.`CategoryDescription`,count(`Professors`.`StaffID`) AS `ProfCount`
FROM `Categories`
LEFT JOIN (
    SELECT
      `faculty_categories`.`CategoryID` AS `CategoryID`,
      `faculty_categories`.`StaffID` AS `StaffID`
    FROM `faculty_categories`
    INNER JOIN `faculty`
      ON `faculty_categories`.`StaffID` = `faculty`.`StaffID`
    WHERE `faculty`.`Title` = 'Professor'
) AS `Professors`
  ON `Categories`.`CategoryID` = `Professors`.`CategoryID`
GROUP BY `Categories`.`CategoryID`
HAVING `ProfCount` < 3;

-- Ex 4
SELECT `Staff`.`StfFirstName`,`Staff`.`StfLastname`,count(`Faculty_Classes`.`ClassID`) AS `ClassCount`
FROM `Staff`
LEFT JOIN `Faculty_Classes`
  ON `Faculty_Classes`.`StaffID` = `Staff`.`StaffID`
GROUP BY `Staff`.`StaffID`
ORDER BY `Staff`.`StfFirstName`,`Staff`.`StfLastname`;
