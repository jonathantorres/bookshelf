-- Ex 1
SELECT `Salary`, CONCAT(`StfLastname`, ', ', `StfFirstName`) AS `StfName` FROM `Staff` ORDER BY `Salary` DESC, `StfName`;

-- Ex 2
SELECT CONCAT(`StfLastname`, ', ', `StfFirstName`) AS `StfName`, CONCAT('(', `StfAreaCode`, ')', ' ', `StfPhoneNumber`) AS `StfPhone` FROM `Staff` ORDER BY `StfName`;

-- Ex 3
SELECT `StudCity`, CONCAT(`StudLastName`, ', ', `StudFirstName`) AS `StudName` FROM `Students` ORDER BY `StudCity`;
