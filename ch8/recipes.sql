-- Ex 1
SELECT `Recipes`.`RecipeTitle` FROM `Recipes`
INNER JOIN `Recipe_Classes`
  ON `Recipes`.`RecipeClassID` = `Recipe_Classes`.`RecipeClassID`
WHERE `Recipe_Classes`.`RecipeClassID` = 4;

-- Ex 2
SELECT DISTINCT `Recipes`.`RecipeTitle` FROM `Recipes`
INNER JOIN `Recipe_Ingredients`
  ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
INNER JOIN `Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
WHERE `Ingredients`.`IngredientClassID` = 8;

-- Ex 3
SELECT `Ingredients1`.`IngredientName` AS `FirstIngredient`, `Ingredients1`.`MeasurementDescription`,`Ingredients2`.`IngredientName` AS `SecondIngredient`
FROM (
    SELECT `Ingredients`.`IngredientID`, `Ingredients`.`IngredientName`,`Measurements`.`MeasurementDescription`,`Ingredients`.`MeasureAmountID`
    FROM `Ingredients`
    INNER JOIN `Measurements`
      ON `Ingredients`.`MeasureAmountID` = `Measurements`.`MeasureAmountID`
) AS `Ingredients1`
INNER JOIN (
    SELECT `Ingredients`.`IngredientID`, `Ingredients`.`IngredientName`,`Measurements`.`MeasurementDescription`,`Ingredients`.`MeasureAmountID`
    FROM `Ingredients`
    INNER JOIN `Measurements`
      ON `Ingredients`.`MeasureAmountID` = `Measurements`.`MeasureAmountID`
) AS `Ingredients2`
  ON (
    `Ingredients1`.`MeasureAmountID` = `Ingredients2`.`MeasureAmountID`
    AND `Ingredients1`.`IngredientName` != `Ingredients2`.`IngredientName`
);

-- Ex 4
SELECT `BeefRecipes`.`RecipeTitle`
FROM (
  SELECT `Recipes`.`RecipeID`, `Recipes`.`RecipeTitle`, `Ingredients`.`IngredientName`, `Ingredients`.`IngredientID`
  FROM `Recipes`
  INNER JOIN `Recipe_Ingredients`
      ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
  INNER JOIN `Ingredients`
    ON `Recipe_Ingredients`.`IngredientID` = `Ingredients`.`IngredientID`
  WHERE `Ingredients`.`IngredientID` = 1
) AS `BeefRecipes`
INNER JOIN (
  SELECT `Recipes`.`RecipeID`, `Recipes`.`RecipeTitle`, `Ingredients`.`IngredientName`, `Ingredients`.`IngredientID`
  FROM `Recipes`
  INNER JOIN `Recipe_Ingredients`
    ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
  INNER JOIN `Ingredients`
    ON `Recipe_Ingredients`.`IngredientID` = `Ingredients`.`IngredientID`
  WHERE `Ingredients`.`IngredientID` = 9
) AS `GarlicRecipes`
  ON `BeefRecipes`.`RecipeID` = `GarlicRecipes`.`RecipeID`;
