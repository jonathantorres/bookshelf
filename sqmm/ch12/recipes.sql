-- Ex 1
SELECT `Recipes`.`RecipeTitle`
FROM `Recipes`
INNER JOIN `Recipe_Ingredients`
  ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
INNER JOIN `Ingredients`
      ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
WHERE `Ingredients`.`IngredientName` = "Garlic"
AND `Recipe_Ingredients`.`Amount` = (
    SELECT MAX(`Recipe_Ingredients`.`Amount`)
    FROM `Recipes`
    INNER JOIN `Recipe_Ingredients`
      ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
    INNER JOIN `Ingredients`
      ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
    WHERE `Ingredients`.`IngredientName` = "Garlic"
);

-- Ex 2
SELECT COUNT(*) AS `TotalMainCourses`
FROM `Recipes`
WHERE `Recipes`.`RecipeClassID` = 1;

-- Ex 3
SELECT SUM(`Recipe_Ingredients`.`Amount`) AS `TeaspoonsAmount`
FROM `Recipes`
INNER JOIN `Recipe_Ingredients`
  ON `Recipes`.`RecipeID` = `Recipe_Ingredients`.`RecipeID`
INNER JOIN `Ingredients`
  ON `Ingredients`.`IngredientID` = `Recipe_Ingredients`.`IngredientID`
WHERE `Ingredients`.`IngredientName` = "Salt";
