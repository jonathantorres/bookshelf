-- Ex 1
SELECT concat(`Students`.`StudFirstName`, ' ', `Students`.`StudLastName`) AS `FullName`,`Students`.`StudStreetAddress` AS `Address`,`Students`.`StudCity` AS `City`,`Students`.`StudState` AS `State`, `Students`.`StudZipCode` AS `ZipCode`
FROM `Students`
UNION
SELECT concat(`Staff`.`StfFirstName`,' ', `Staff`.`StfLastname`) AS `FullName`,`Staff`.`StfStreetAddress`, `Staff`.`StfCity`,`Staff`.`StfState`,`Staff`.`StfZipCode`
FROM `Staff`
ORDER BY `ZipCode`;
