-- Ex 1
SELECT `Ingredients`.`IngredientName`,`Measurements`.`MeasurementDescription`,'Ingredient' AS `Type`
FROM `Ingredients`
INNER JOIN `Measurements`
  ON `Measurements`.`MeasureAmountID` = `Ingredients`.`MeasureAmountID`
UNION
SELECT `Ingredients`.`IngredientName`,`Measurements`.`MeasurementDescription`,'Recipe' AS `Type`
FROM `Ingredients`
INNER JOIN `Recipe_Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
INNER JOIN `Measurements`
  ON `Recipe_Ingredients`.`MeasureAmountID` = `Measurements`.`MeasureAmountID`;
