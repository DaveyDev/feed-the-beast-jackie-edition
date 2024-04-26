#ifndef COFFEE_SEED_MANAGER_H
#define COFFEE_SEED_MANAGER_H

#include "raylib.h"
#include "coffeeSeed.h"  // Include CoffeeSeed type definition
#include "player.h"      // Include Player type definition

#define MAX_COFFEE_SEEDS 2048

typedef struct {
    CoffeeSeed coffeeSeed[MAX_COFFEE_SEEDS];
    int numSeeds;
} CoffeeSeedManager;

// Function prototypes related to CoffeeSeedManager
//void spawnCoffeeSeed(CoffeeSeedManager *coffeeSeedManager, Vector2 position, Camera2D camera);
//void drawCoffeeSeed(CoffeeSeedManager *coffeeSeedManager, Camera2D camera);
//void updateCoffeeSeed(CoffeeSeed *coffeeSeed);
//void interactWithCoffeeSeeds(Player *player, CoffeeSeedManager *coffeeSeedManager);
//void unloadCoffeeSeeds(CoffeeSeedManager *coffeeSeedManager);

#endif  // COFFEE_SEED_MANAGER_H
