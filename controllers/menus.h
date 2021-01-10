#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "./controller.h"
#define RIGHT 77
#define LEFT 75
#define EXIT 27
#define ENTER 13
#define CLEAR system("cls || clear")

void printHomePage(Recipe *recipes) {
  bool inMenu = true;
  while(inMenu) {
    int menu = 0;
    while(!(menu >= 1 && menu <= 3)) {
      CLEAR;
      puts(" === HomePage ===");
      puts("1. Recipes suggestions");
      puts("2. Search");
      puts("3. Back to main screen");
      printf(">> "); scanf("%d", &menu); getchar();
      switch(menu) {
        case 1:
          printAllRecipe(recipes);
          break;
        case 2:
          printSearch(recipes);
        break;
        case 3:
          inMenu = false;
        break;
      }
    }
  }
  fflush(stdin);
}

void printCookBook(User *user, Recipe *recipes) {
  bool inMenu = true;
  while(inMenu) {
    int menu = 0;
    while(!(menu >= 1 && menu <= 3)) {
      CLEAR;
      Recipe *addedRecipe = NULL;
      Recipe *deletedRecipe = NULL;
      puts(" === CookBook ===");
      puts("1. Saved recipes");
      puts("2. Add recipes from online recipes");
      puts("3. Manually add recipes");
      puts("4. Delete saved recipes");
      puts("5. Back to main screen");
      printf(">> "); scanf("%d", &menu); getchar();
      switch(menu) {
        case 1:
          printAllRecipe(user->savedRecipes);
        break;
        case 2:
          addedRecipe = selectRecipe(recipes);
          if(addedRecipe) {
            if(checkUserRecipe(user, addedRecipe)) {
              addRecipe(user->savedRecipes, addedRecipe);
              CLEAR;
              puts("Recipe succesfuly added to user's saved recipes"); getchar();
            } else {
              CLEAR;
              puts("The recipe is already exists on user's saved recipes!"); getchar();
            }
          }
        break;
        case 4:
          deletedRecipe = selectRecipe(user->savedRecipes);
          if(deletedRecipe) {
            deleteRecipe(user, deletedRecipe);
          }
        case 5:
          inMenu = false;
        break;
      }
    }
  }
  fflush(stdin);
} 

//Menu for Kitchen
void kitchenMenu(User *user, Recipe *recipes){
  bool inMenu = true;
  while (inMenu){
    CLEAR;
    puts("Hello Welcome To THe Kitchen!");
    puts("Enter <<EXIT>> to exit from menu");
    puts("List of Dishes from Cookbook:");
    printAllRecipe(user->savedRecipes);
    puts("");
    printf("===========================\n");
    puts("What would you like to cook today?");
    char temprecipe[255];
    scanf("%[^\n]", temprecipe);
    if (strcmp(temprecipe, "EXIT")==0){
      inMenu = false;
      return;
    }else{
      int x = 0;
      x = searchFoodExist(temprecipe,user);//if food exits return 1
      if (x == 0){
        puts("The food you want to cook isn't registered :(");
      }else{
        puts("Okay, 1st lets prepare the ingredients!");
        printf("To cook %s you will need:", temprecipe);
        printIngredientofFood(temprecipe, recipes);//ngeloop ingredient yg dibutuhkan untuk makanan tsb
        puts("");
        int continuebutton = 0;
        puts("To continue to instructions enter <<1>>");
        while (continuebutton != 1){
         scanf("%d", &continuebutton); 
        }
        if (continuebutton == 1){
          printf("Okay here, are the steps in making %s:", temprecipe);
          puts("GoodLuck!");
          printInstructionofFood(temprecipe, recip);//ngeloop pake getchar() instruksi u/ makanan tsb
          puts("Amazing, thats all the steps done!");
          puts("I'm hoping the food is delicious!");
          puts("Enter <<1>> to exit from kitchen:");
          int exitbutton = 0;
          while (exitbutton!= 1){
            scanf("%d", &exitbutton);
          }
          if (exitbutton == 1){
            inMenu = false;
            return;
          }
        }
      }
    }
  }
}
