#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "../models/model.h"
#define RIGHT 77
#define LEFT 75
#define EXIT 27
#define ENTER 13
#define CLEAR system("cls || clear")

Instruction *newInstruction(const char *desc) {
  Instruction *temp = (Instruction*)malloc(sizeof(Instruction));
  strcpy(temp->desc, desc);
  temp->prev = temp->next = NULL;
  return temp;
}
Ingredient *newIngredient(const char *name, int qty, int exp) {
  Ingredient *temp = (Ingredient*)malloc(sizeof(Ingredient));
  strcpy(temp->name, name);
  temp->qty = qty;
  temp->exp = exp;
  temp->prev = temp->next = NULL;
  return temp;
}
Recipe *newRecipe(const char *name, const char *desc) {
  Recipe *temp = (Recipe*)malloc(sizeof(Recipe));
  strcpy(temp->name, name);
  strcpy(temp->desc, desc);
  temp->instructions = NULL;
  temp->ingredients = NULL;
  temp->prev = temp->next = NULL;
  return temp;
}
User *newUser(const char *name) {
  User *temp = (User*)malloc(sizeof(User));
  strcpy(temp->name, name);
  temp->savedRecipes = NULL;
  temp->prev = temp->next = NULL;
  return temp;
}
void addUser(User *&users, User *user) {
  if(!users) users = user;
  else {
    user->next = users;
    users->prev = user;
    users = user;
  }
}
void addInstruction(Instruction *&instruction, Instruction *newInstruction) {
  if(!instruction) instruction = newInstruction;
  else {
    Instruction *temp = instruction;
    while(temp->next) temp = temp->next;
    temp->next = newInstruction;
    newInstruction->prev = temp;
  }
}
void addIngredient(Ingredient *&ingredient, Ingredient *newIngredient) {
  if(!ingredient) ingredient = newIngredient;
  else {
    Ingredient *temp = ingredient;
    while(temp->next) temp = temp->next;
    temp->next = newIngredient;
    newIngredient->prev = temp;
  }
}
void addRecipe(Recipe *&recipes, Recipe *newRecipe) {
  if(!recipes) recipes = newRecipe;
  else {
    newRecipe->next = recipes;
    recipes->prev = newRecipe;
    recipes = newRecipe;
  }
}
void printInstruction(Instruction *instruction) {
  if(!instruction) {
    puts("No instructions added!");
    return;
  } else {
    int idx = 1;
    Instruction *temp = instruction;
    while(temp) {
      int input = -1;
      printf("Step #%02d:\n", idx++);
      printf("%s\n", temp->desc);
      temp = temp->next;
    }
  }
}
void printIngredient(Ingredient *ingredient) {
  if(!ingredient) {
    puts("No ingredients added!");
    return;
  } else {
    int idx = 1;
    Ingredient *temp = ingredient;
    printf("No. %-20s|qty|exp\n", "Nama Bahan");
    while(temp) {
      printf("%02d. %-20s|%03d|%02d day\n", idx++, temp->name, temp->qty, temp->exp);
      temp = temp->next;
    }
  }
}
// print a recipe
void printRecipe(Recipe *recipe) {
  if(!recipe) return;
  else {
    printf("Name:\n%s\n", recipe->name);
    printf("Desc:\n%s\n", recipe->desc);
    puts("Ingredient:");
    printIngredient(recipe->ingredients);
    puts("Instructions:");
    printInstruction(recipe->instructions);
  }
}
// print availale recipes
void printSearch(Recipe *recipe) {
  CLEAR;
  if(!recipe) {
    puts(" === Search ===");
    puts("There is no recipe on data, please add some!"); getchar();
    return;
  } else {
    Recipe *temp = recipe;
    char name[255];
    puts(" === Search ===");
    puts("type 0 to return");
    printf(">> "); scanf("%[^\n]", name); getchar();
    if(name[0] == '0') return;
    else {
      bool found = false;
      while(temp) {
        if(strcmp(temp->name, name) == 0) {
          CLEAR;
          printRecipe(temp);
          puts("Press enter to continue..."); getchar();
          found = true;
          break;
        }
        temp = temp->next;
      }
      if(!found) {
        CLEAR;
        puts("The recipe is not exist!\nplease make sure you type exactly the same name of the recipe.\nPress enter to continue..."); getchar();
      }
    }
  }
}
// print available recipes
void printAllRecipe(Recipe *recipe) {
  if(!recipe) {
    CLEAR;
    puts(" === Recipes ===");
    puts("There is no recipe on data, please add some!"); getchar();
    return;
  } else {
    Recipe *temp = recipe;
    char keyPress = 0;
    while(keyPress != 27) {
      keyPress = 0;
      do {
        CLEAR;
        puts(" === Recipes ===");
        printRecipe(temp);
        printf("\n   [<] = prev   [>] = next   [Esc] = Back\n");
        keyPress = getch();
        if(keyPress == LEFT && temp->prev) temp = temp->prev; 
        else if(keyPress == RIGHT && temp->next) temp = temp->next; 
      } while(keyPress == 75 || keyPress == 77);
    }
  }
  fflush(stdin);
}
// select a recipe from recipe list
Recipe *selectRecipe(Recipe *recipe) {
  if(!recipe) {
    CLEAR;
    puts(" === Recipes ===");
    puts("There is no recipe on data, please add some!"); getchar();
  } else {
    Recipe *temp = recipe;
    char keyPress = 0;
    while(keyPress != EXIT) {
      keyPress = 0;
      do {
        CLEAR;
        puts(" === Recipes ===");
        printRecipe(temp);
        printf("\n   [<] = prev   [>] = next   [Esc] = Back  [Enter] = Confirm\n");
        keyPress = getch();
        if(keyPress == LEFT && temp->prev) {
          temp = temp->prev;
        } else if(keyPress == RIGHT && temp->next) {
          temp = temp->next; 
        } 
      } while(keyPress == LEFT || keyPress == RIGHT);
      if(keyPress == ENTER) {
        keyPress = EXIT;
        Recipe *savedRecipe = newRecipe(temp->name, temp->desc);
        savedRecipe->ingredients = temp->ingredients;
        savedRecipe->instructions = temp->instructions;
        return savedRecipe;
      }
    }
  }
  return NULL;
}
// delete recipe from recipe list
void deleteRecipe(User *&user, Recipe *deletedRecipe) {
  if(!user->savedRecipes->next) { 
    if(strcmp(user->savedRecipes->name, deletedRecipe->name) == 0) {
    user->savedRecipes = NULL;
    free(user->savedRecipes);
    }
  }
  else {
    bool isFound = false;
    Recipe *tempRecipe = user->savedRecipes;
    while(tempRecipe)  {
      if(strcmp(tempRecipe->name, deletedRecipe->name) == 0) {
        isFound = true;
        break;
      }
      tempRecipe = tempRecipe->next;
    }
    if(isFound) {
      if(!tempRecipe->next) {
        Recipe *temp = tempRecipe->prev;
        temp->next = tempRecipe->prev = NULL;
        free(tempRecipe);
        tempRecipe = temp;
      } else if(!tempRecipe->prev) {
        if(strcmp(user->savedRecipes->name, deletedRecipe->name) == 0) {
          user->savedRecipes = NULL;
          free(user->savedRecipes);
        }
      } else {
        tempRecipe->next = deletedRecipe;
        deletedRecipe->next->prev = tempRecipe;
        deletedRecipe->prev =  deletedRecipe->next = NULL;
        free(deletedRecipe);
        deletedRecipe = NULL;
      }
    }
  }
}
// check if user saved recipe exist
bool checkUserRecipe(User *user, Recipe *recipe) {
  Recipe *temp = user->savedRecipes;
  while(temp) {
    if(strcmp(temp->name, recipe->name) == 0) return false;
    temp = temp->next;
  }
  return true;
}


//Function for Kitchen//
//Search if Food is within user's cookbook
int searchFoodExist (const char str[], User *user){
  Recipe *curr = user->savedRecipes;
  while (curr){
    if ( strcmp(curr->name, str)==0){
      return 1;//ketemu
    }
    curr = curr->next;
  }
  return -1;//alias g ada di cookbook
}
//Looping required Ingredient of food
void printIngredientofFood(const char str[], Recipe *recipes){
  Recipe *curr = recipes;
  while (curr){
    if (strcmp(curr->name, str)== 0){
      Ingredient *currin = curr->ingredients;
      while (currin){
        printf("%s.......%s\n", currin->name, currin->qty);
        currin = currin->next;
      }
    } 
    curr = curr->next;
  }
}
//Looping through instructiosn of food with getchar(1);
void printInstructionofFood(const char str[], Recipe *recipes){
  Recipe *curr = recipes;
  while (curr){
    if (strcmp (curr->name, str)==0){
      Instruction *currin = curr->instructions;
      int idx = 1;
      int nextbutton = 0;
      while ( currin){
        printf("Step %d:\n", idx);
        printf("%s\n", currin->desc);
        puts("");
        printf("Enter 1 to go to next step: ");
        while (nextbutton != 1){
          scanf("%d", &nextbutton);
        }
        if (nextbutton == 1){
          idx++;
          puts("");
        }
        currin = currin->next;
      }
    }
    curr= curr->next;
  }
}
