-- Ex 1
SELECT `Staff`.`StfFirstName`,`Staff`.`StfLastname`,(
    SELECT count(*)
    FROM `Faculty_Classes`
    WHERE `Faculty_Classes`.`StaffID` = `Staff`.`StaffID`
) AS `ClassCount`
FROM `Staff`;

-- Ex 2
SELECT `Students`.`StudFirstName`,`Students`.`StudLastName`
FROM `Students`
WHERE `Students`.`StudentID` IN(
    SELECT DISTINCT `Students`.`StudentID`
    FROM `Students`
    INNER JOIN `Student_Schedules`
      ON `Students`.`StudentID` = `Student_Schedules`.`StudentID`
    INNER JOIN `Classes`
      ON `Classes`.`ClassID` = `Student_Schedules`.`ClassID`
    WHERE `Classes`.`TuesdaySchedule` = 1
);

-- Ex 3
SELECT `Subjects`.`SubjectName`
FROM `Subjects`
WHERE `Subjects`.`SubjectID` IN(
    SELECT DISTINCT `Subjects`.`SubjectID`
    FROM `Subjects`
    INNER JOIN `Classes`
      ON `Subjects`.`SubjectID` = `Classes`.`SubjectID`
    WHERE `Classes`.`WednesdaySchedule` = 1
);
