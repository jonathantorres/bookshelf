-- Ex 1
SELECT `Buildings`.`BuildingName`,`Class_Rooms`.`ClassRoomID`
FROM `Buildings`
INNER JOIN `Class_Rooms`
  ON `Buildings`.`BuildingCode` = `Class_Rooms`.`BuildingCode`;

-- Ex 2
SELECT `Classes`.`ClassID`, concat(`Students`.`StudFirstName`, ' ', `Students`.`StudLastName`) AS `StudName`, `Subjects`.`SubjectName`
FROM `Students`
INNER JOIN `Student_Schedules`
  ON `Students`.`StudentID` = `Student_Schedules`.`StudentID`
INNER JOIN `Classes`
  ON `Student_Schedules`.`ClassID` = `Classes`.`ClassID`
INNER JOIN `Subjects`
  ON `Classes`.`SubjectID` = `Subjects`.`SubjectID`
WHERE `Student_Schedules`.`ClassStatus` = 1;

-- Ex 3
SELECT concat(`Staff`.`StfFirstName`, ' ', `Staff`.`StfLastname`) AS `StfName`, `Faculty`.`Title`, `Subjects`.`SubjectName`
FROM `Faculty`
INNER JOIN `Staff`
  ON `Faculty`.`StaffID` = `Staff`.`StaffID`
INNER JOIN `Faculty_Subjects`
  ON `Staff`.`StaffID` = `Faculty_Subjects`.`StaffID`
INNER JOIN `Subjects`
  ON `Subjects`.`SubjectID` = `Faculty_Subjects`.`SubjectID`;

-- Ex 4
SELECT `ArtStudents`.`StudFullName`
FROM (
  SELECT `Students`.`StudentID`,concat(`Students`.`StudFirstName`, ' ',   `Students`.`StudLastName`) AS `StudFullName`, `Classes`.`ClassID`,`Student_Schedules`.`Grade`, `Categories`.`CategoryID`, `Categories`.`CategoryDescription`
  FROM `Students`
  INNER JOIN `Student_Schedules`
    ON `Students`.`StudentID` = `Student_Schedules`.`StudentID`
  INNER JOIN `Classes`
    ON `Classes`.`ClassID` = `Student_Schedules`.`ClassID`
  INNER JOIN `Subjects`
    ON `Subjects`.`SubjectID` = `Classes`.`SubjectID`
  INNER JOIN `Categories`
    ON `Categories`.`CategoryID` = `Subjects`.`CategoryID`
  WHERE `Student_Schedules`.`ClassStatus` = 2
  AND `Categories`.`CategoryID` IN ('ART')
  AND `Student_Schedules`.`Grade` >= 85
) AS `ArtStudents`
INNER JOIN (
  SELECT `Students`.`StudentID`,concat(`Students`.`StudFirstName`, ' ', `Students`.`StudLastName`) AS `StudFullName`, `Classes`.`ClassID`,`Student_Schedules`.`Grade`, `Categories`.`CategoryID`, `Categories`.`CategoryDescription`
  FROM `Students`
  INNER JOIN `Student_Schedules`
    ON `Students`.`StudentID` = `Student_Schedules`.`StudentID`
  INNER JOIN `Classes`
    ON `Classes`.`ClassID` = `Student_Schedules`.`ClassID`
  INNER JOIN `Subjects`
    ON `Subjects`.`SubjectID` = `Classes`.`SubjectID`
  INNER JOIN `Categories`
    ON `Categories`.`CategoryID` = `Subjects`.`CategoryID`
  WHERE `Student_Schedules`.`ClassStatus` = 2
  AND `Categories`.`CategoryID` IN ('CIS', 'CSC')
  AND `Student_Schedules`.`Grade` >= 85
) AS `ComputerStudents`
  ON `ArtStudents`.`StudentID` = `ComputerStudents`.`StudentID`;
