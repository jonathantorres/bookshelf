-- Ex 1
SELECT `Recipe_Classes`.`RecipeClassDescription`,sum(`Recipe_Ingredients`.`Amount`) AS `TsAmount`
FROM `Recipe_Classes`
INNER JOIN `Recipes`
  ON `Recipe_Classes`.`RecipeClassID` = `Recipes`.`RecipeClassID`
INNER JOIN `Recipe_Ingredients`
  ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
INNER JOIN `Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
WHERE `Ingredients`.`IngredientName` = "Salt"
GROUP BY `Recipe_Classes`.`RecipeClassID`
HAVING `TsAmount` > 3;


-- Ex 2
SELECT `Recipe_Classes`.`RecipeClassDescription`, COUNT(`Recipes`.`RecipeID`) AS `NumofRecipes`
FROM `Recipe_Classes`
INNER JOIN `Recipes`
  ON `Recipe_Classes`.`RecipeClassID` = `Recipes`.`RecipeClassID`
GROUP BY `Recipe_Classes`.`RecipeClassID`
HAVING `NumofRecipes` >= 2;
