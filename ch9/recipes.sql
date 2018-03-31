-- Ex 1
SELECT `Recipe_Classes`.`RecipeClassDescription`
FROM `Recipe_Classes`
LEFT JOIN `Recipes`
  ON `Recipes`.`RecipeClassID` = `Recipe_Classes`.`RecipeClassID`
WHERE `Recipes`.`RecipeID` IS NULL;

-- Ex 2
SELECT `Ingredients`.`IngredientName`,`Recipes`.`RecipeTitle`
FROM `Ingredients`
LEFT JOIN `Recipe_Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
LEFT JOIN `Recipes`
  ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
ORDER BY `Ingredients`.`IngredientName`;

-- Ex 3
SELECT `Recipe_Classes`.`RecipeClassDescription`,`Recipes`.`RecipeTitle`
FROM `Recipe_Classes`
LEFT JOIN `Recipes`
  ON `Recipes`.`RecipeClassID` = `Recipe_Classes`.`RecipeClassID`
WHERE `Recipe_Classes`.`RecipeClassID` IN(1,4,7);

-- Ex 4
SELECT `Recipe_Classes`.`RecipeClassDescription`,`Recipes`.`RecipeTitle`
FROM `Recipe_Classes`
LEFT JOIN `Recipes`
  ON `Recipes`.`RecipeClassID` = `Recipe_Classes`.`RecipeClassID`;
