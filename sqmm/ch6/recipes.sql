-- Ex 1
SELECT * FROM `Recipes` WHERE `RecipeClassID` = 1 AND `Notes` IS NOT NULL;

-- Ex 2
SELECT * FROM `Recipes` WHERE `RecipeID` BETWEEN 1 AND 5;
