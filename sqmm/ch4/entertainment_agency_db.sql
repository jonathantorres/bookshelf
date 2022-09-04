-- Ex 1
SELECT `AgtLastName`, `AgtFirstName`, `AgtPhoneNumber` FROM `Agents` ORDER BY `AgtLastName`, `AgtFirstName`;

-- Ex 2
SELECT * FROM `Engagements`;

-- Ex 3
SELECT `EngagementNumber`,`StartDate` FROM `Engagements` ORDER BY `StartDate` DESC, `EngagementNumber` ASC;
