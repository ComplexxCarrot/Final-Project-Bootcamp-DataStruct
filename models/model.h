struct Instruction {
  char desc[255]; // deskripsi instruksi per step
  Instruction *prev, *next;
};
struct Ingredient {
  char name[255]; // nama bahan
  int qty; // jumlah bahan
  int exp; // berapa hari bahan itu expired
  Ingredient *prev, *next;
};
struct Recipe {
  char name[255]; // nama masakan
  char desc[255]; // deskripsi masakan
  Instruction *instructions;
  Ingredient *ingredients;
  Recipe *prev, *next;
};
struct User {
  char name[255];
  Recipe *savedRecipes;
  User *prev, *next;
};
