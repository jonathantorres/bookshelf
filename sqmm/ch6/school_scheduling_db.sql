-- Ex 1
SELECT `StfFirstName`,`StfLastname`,`StfStreetAddress` FROM `Staff` WHERE `StfStreetAddress` LIKE '%Box%' ORDER BY `StfFirstName`;

-- Ex 2
SELECT * FROM `Students` WHERE `StudState` NOT IN('OR','WA','ID');

-- Ex 3
SELECT * FROM `Subjects` WHERE `SubjectCode` LIKE 'MUS%';
