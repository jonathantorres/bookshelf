-- Ex 1
SELECT
   `Subjects`.`SubjectName` AS `SubjectName`,
   `Classes`.`ClassRoomID` AS `ClassRoomID`,
   `Classes`.`StartTime` AS `StartTime`,
   `Classes`.`Duration` AS `Duration`
FROM `Subjects`
INNER JOIN `Classes`
  ON `Subjects`.`SubjectID` = `Classes`.`SubjectID`
LEFT JOIN `ch09_classes_students` AS `Enrolled`
  ON `Classes`.`ClassID` = `Enrolled`.`ClassID`
WHERE `Enrolled`.`ClassID` IS NULL;

-- Ex 2
SELECT `Subjects`.`SubjectName` FROM `Subjects`
LEFT JOIN `Faculty_Subjects`
  ON `Subjects`.`SubjectID` = `Faculty_Subjects`.`SubjectID`
LEFT JOIN `Staff`
  ON `Staff`.`StaffID` = `Faculty_Subjects`.`StaffID`
WHERE `Staff`.`StaffID` IS NULL;

-- Ex 3
SELECT `Students`.`StudFirstName`, `Students`.`StudLastName`
FROM `Students`
LEFT JOIN (
    SELECT * FROM `Student_Schedules` WHERE `ClassStatus` = 1
) AS `Enrolled_Students`
ON `Students`.`StudentID` = `Enrolled_Students`.`StudentID`
WHERE `Enrolled_Students`.`StudentID` IS NULL;

-- Ex 4
SELECT concat(`Staff`.`StfFirstName`, ' ', `Staff`.`StfLastname`) AS `StaffName`,`Subjects`.`SubjectName`,`Classes`.`ClassID`,`Classes`.`ClassRoomID`, `Classes`.`StartTime`,`Classes`.`Duration`
FROM `Staff`
LEFT JOIN `Faculty_Classes`
  ON `Staff`.`StaffID` = `Faculty_Classes`.`StaffID`
LEFT JOIN `Classes`
  ON `Classes`.`ClassID` = `Faculty_Classes`.`ClassID`
LEFT JOIN `Subjects`
  ON `Subjects`.`SubjectID` = `Classes`.`SubjectID`;
