-- Ex 1
SELECT `Recipe_Classes`.`RecipeClassDescription`,(
    SELECT count(*)
    FROM `Recipes`
    WHERE `Recipes`.`RecipeClassID` = `Recipe_Classes`.`RecipeClassID`
) AS `RecipeCount`
FROM `Recipe_Classes`;

-- Ex 2
SELECT DISTINCT `Outer_Ingredients`.`IngredientID`,`Outer_Ingredients`.`IngredientName`,`Outer_Ingredients`.`MeasureAmountID`
FROM `Ingredients` AS `Outer_Ingredients`
INNER JOIN `Recipe_Ingredients` AS `Outer_Recipe_Ingredients`
  ON `Outer_Ingredients`.`IngredientID` = `Outer_Recipe_Ingredients`.`IngredientID`
WHERE `Outer_Recipe_Ingredients`.`MeasureAmountID` <> SOME(
    SELECT `Ingredients`.`MeasureAmountID`
    FROM `Ingredients`
    WHERE `Ingredients`.`IngredientID` = `Outer_Ingredients`.`IngredientID`
 )
 ORDER BY `Outer_Ingredients`.`IngredientID`;
