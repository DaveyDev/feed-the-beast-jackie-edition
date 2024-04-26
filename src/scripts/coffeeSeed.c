#include "coffeeSeedManager.h"
#include "coffeeSeed.h"

void spawnCoffeeSeed(CoffeeSeedManager *coffeeSeedManager, Vector2 position, Camera2D camera) {
    if (coffeeSeedManager->numSeeds < MAX_COFFEE_SEEDS) {
        CoffeeSeed *coffeeSeed = &coffeeSeedManager->coffeeSeed[coffeeSeedManager->numSeeds];
        coffeeSeed->position = position;
        coffeeSeed->texture = LoadTexture("src/textures/coffeeSeed.png");
        coffeeSeed->isActive = true;
        coffeeSeed->isEquipped = false;
        coffeeSeed->collider = (Rectangle){ position.x, position.y, 64, 64 };
        
        coffeeSeedManager->numSeeds++;
    }
}

void drawCoffeeSeeds(CoffeeSeedManager *coffeeSeedManager, Camera2D camera) {
    BeginMode2D(camera);
    for (int i = 0; i < coffeeSeedManager->numSeeds; i++) {
        CoffeeSeed *coffeeSeed = &coffeeSeedManager->coffeeSeed[i];
        if (coffeeSeed->isActive) {
            DrawTexture(coffeeSeed->texture, coffeeSeed->position.x, coffeeSeed->position.y, WHITE);
        }
    }
    EndMode2D();
}

void updateCoffeeSeed(CoffeeSeed *coffeeSeed) {
    // Implement update logic for CoffeeSeed
}

void interactWithCoffeeSeeds(Player *player, CoffeeSeedManager *coffeeSeedManager) {
    for (int i = 0; i < coffeeSeedManager->numSeeds; i++) {
        CoffeeSeed *coffeeSeed = &coffeeSeedManager->coffeeSeed[i];
        
        if (CheckCollisionRecs(player->collider, coffeeSeed->collider) && coffeeSeed->isActive) {
            coffeeSeed->isActive = false;
            player->points++;
            // Additional interactions when player picks up coffee seed
        }
    }
}

void unloadCoffeeSeeds(CoffeeSeedManager *coffeeSeedManager) {
    for (int i = 0; i < coffeeSeedManager->numSeeds; i++) {
        UnloadTexture(coffeeSeedManager->coffeeSeed[i].texture);
    }
    coffeeSeedManager->numSeeds = 0; // Reset seed count
}
