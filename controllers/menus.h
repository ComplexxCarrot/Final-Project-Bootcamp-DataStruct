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
    while(!(menu >= 1 && menu <= 5)) {
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
        case 3: 
        {
          // name
          char name[255], desc[255];
          bool isValid = true;
          bool Quit = false;
          do {
            isValid = true;
            CLEAR;
            puts(" === Add Recipe ===");
            printf("Recipe name [1..25]: ");
            scanf("%[^\n]", name); getchar();

            if(!(strlen(name) >= 1 && strlen(name) <= 25)) isValid = false;
          } while(!isValid);
          // desc
          do {
            isValid = true;
            CLEAR;
            puts(" === Add Recipe ===");
            printf("Recipe name [1..25]: %s\n", name);
            printf("Recipe desc [1..100]:\n");
            scanf("%[^\n]", desc); getchar();
            if(!(strlen(desc) >= 1 && strlen(name) <= 100)) isValid = false;
          } while(!isValid);

          // ingredients
          Ingredient *tempIngredients = NULL;
          do {
            char ingredientName[255];
            int ingredientQty, ingredientExp;
            CLEAR;
            puts(" === Add Recipe ===");
            printf("Recipe name [1..25]: %s\n", name);
            printf("Recipe desc [1..100]:\n%s\n", desc);
            printf("Recipe ingredient [-1 to cancel|| -2 to finish]:\n");
            do {
              isValid = true;
              printf("Ingredient name [1..25]: "); scanf("%s", ingredientName); getchar();
              if(!(strlen(ingredientName) >= 1 && strlen(ingredientName) <= 25)) isValid = false;
            } while(!isValid);
            if(strcmp(ingredientName, "-1") == 0) {
              Quit = true;
              break;
            } else if(strcmp(ingredientName, "-2") == 0) break;
            printf("Ingredient Qty: "); scanf("%d", &ingredientQty); getchar();
            if(ingredientQty == -1) {
              Quit = true;
              break;
            } else if(ingredientQty == -2) break;
            printf("Ingredient Exp day(s): "); scanf("%d", &ingredientExp); getchar();
            if(ingredientExp == -1) {
              Quit = true;
              break;
            } else if(ingredientExp == -2) break;
            addIngredient(tempIngredients, newIngredient(ingredientName, ingredientQty, ingredientExp));
            printf("Ingredient added to recipe!"); getchar();
          } while(true);

          Instruction *tempInstructions = NULL;
          if(!Quit) {
            do {
              char instructionDesc[255];
              CLEAR;
              puts(" === Add Recipe ===");
              printf("Recipe name [1..25]: %s\n", name);
              printf("Recipe desc [1..100]:\n%s\n", desc);
              printf("Recipe instructions [-1 to quit || -2 to finish]:\n");
              scanf("%[^\n]", instructionDesc); getchar();
              if(strcmp(instructionDesc, "-1") == 0) {
                Quit = true;
                break;
              } else if(strcmp(instructionDesc, "-2") == 0) break;
              addInstruction(tempInstructions, newInstruction(instructionDesc));
              printf("Instruction added to the recipe!"); getchar();
            } while(true);
          }
          if(!Quit) {
            addRecipe(user->savedRecipes, newRecipe(name, desc));
            addIngredient(user->savedRecipes->ingredients, tempIngredients);
            addInstruction(user->savedRecipes->instructions, tempInstructions);
            printf("Recipe added to user's recipe book!"); getchar();
          }
          fflush(stdin);
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
    puts("Press ESC to exit from menu");
    puts("Select a dish from Cookbook:");
    printf("===========================\n"); getchar();
    Recipe *selectedRecipe = selectRecipe(user->savedRecipes);
    if(selectedRecipe == NULL) {
      inMenu = false;
      break;
    }
    else{
      CLEAR;
      puts("Okay, 1st lets prepare the ingredients!");
      printf("To cook %s you will need:\n", selectedRecipe->name); 
      printIngredient(selectedRecipe->ingredients);
      char continuebutton = 0;
      puts("To continue to instructions press [Enter]\nTo quit press [Esc]");
      while (!(continuebutton == ENTER || continuebutton == EXIT)){
        continuebutton = getch();
      }
      CLEAR;
      if (continuebutton == ENTER){
        printf("Okay here, are the steps in making %s:\n", selectedRecipe->name);
        puts("GoodLuck!"); getchar();
        CLEAR;
        // validasi kalo gaada instruksi
        if(!selectedRecipe->instructions) {
          puts("No instructions added to this recipe!");
          puts("Press enter to exit."); getchar();
          inMenu = false;
          break;
        }
        printInstructionPerStep(selectedRecipe->instructions);
        puts("Amazing, thats all the steps done!");
        puts("I'm hoping the food is delicious!");
        puts("Press enter to exit from kitchen:"); getchar();
        inMenu = false;
      }
    }
  }
}
