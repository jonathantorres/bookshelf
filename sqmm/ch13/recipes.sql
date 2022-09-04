-- Ex 1
SELECT `Ingredients`.`IngredientName`,`Measurements`.`MeasurementDescription`,sum(`Recipe_Ingredients`.`Amount`) AS `TotalAmount`
FROM `Recipe_Ingredients`
INNER JOIN `Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
INNER JOIN `Measurements`
  ON `Measurements`.`MeasureAmountID` = `Recipe_Ingredients`.`MeasureAmountID`
GROUP BY `Ingredients`.`IngredientID`, `Measurements`.`MeasurementDescription`
ORDER BY `Ingredients`.`IngredientName`;


-- Ex 2
SELECT `Ingredient_Classes`.`IngredientClassDescription`,`Ingredients`.`IngredientName`,count(`Recipe_Ingredients`.`IngredientID`) AS `RecipeCount`
FROM `Ingredients`
INNER JOIN `Recipe_Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
INNER JOIN `Ingredient_Classes`
  ON `Ingredient_Classes`.`IngredientClassID` = `Ingredients`.`IngredientClassID`
WHERE `Ingredients`.`IngredientClassID` = 2
GROUP BY `Ingredients`.`IngredientID`;


-- Ex 3
SELECT (
    SELECT `Ingredient_Classes`.`IngredientClassDescription`
    FROM `Ingredient_Classes`
    WHERE `Ingredient_Classes`.`IngredientClassID` = `Ingredients`.`IngredientClassID`
) AS `IngredientClassDescription`, `Ingredients`.`IngredientName`, (
    SELECT count(*)
    FROM `Recipe_Ingredients`
    WHERE `Recipe_Ingredients`.`IngredientID` = `Ingredients`.`IngredientID`
) AS `RecipeCount`
FROM `Ingredients`
WHERE `Ingredients`.`IngredientClassID` = 2;
