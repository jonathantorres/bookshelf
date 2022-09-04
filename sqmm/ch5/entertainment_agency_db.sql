-- Ex 1
SELECT `CustCity`, CONCAT(`CustFirstName`, ' ', `CustLastName`) AS `CustName` FROM `Customers` ORDER BY `CustCity`;

-- Ex 2
SELECT `EntStageName`, `EntWebPage` FROM `Entertainers`;

-- Ex 3
SELECT CONCAT(`AgtLastName`, ', ', `AgtFirstName`) AS `AgtName`, `DateHired`, DATE_ADD(`DateHired`, INTERVAL 6 MONTH) AS `FirstReview` FROM `Agents` ORDER BY `AgtName`;
