#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../controllers/menus.h"
#define gtc getchar
#define ll long long int

int main(){
  Recipe *recipes = NULL;
  User *users = NULL;

  addUser(users, newUser("Chiko"));
  addRecipe(recipes, newRecipe("Ayam Goreng", "Ayam goreng kesukaan ipin"));
  addRecipe(recipes, newRecipe("Nasi Goreng", "Nasi goreng top buatan uncle mutu"));

  // Main Screen
  bool inMenu = true;
  while(inMenu) {
    int menu = 0;
    while(!(menu >= 1 && menu <= 6)) {
      CLEAR;
      puts(" === Main Menu === ");
      puts("1. Home Page");
      puts("2. Cook Book");
      puts("3. Kitchen");
      puts("4. Pantry");
      puts("5. Profile");
      puts("6. Exit");
      printf(">> "); scanf("%d", &menu); gtc();
      switch(menu) {
        case 1:
          printHomePage(recipes);
          break;
        case 2:
          printCookBook(users, recipes);
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          inMenu = false;
          break;
      }
    }
  }
  CLEAR;
  return 0;
}