#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "coffeeSeed.h"
#include "coffeeSeedManager.h"
#include "constants.h"  // Include CoffeeSeedManager type definition



typedef struct {
    Vector2 position;
    Texture2D texture;
    float speed;
    Rectangle collider;
    Rectangle colliderDown;
    Rectangle colliderUp;
    Rectangle colliderLeft;
    Rectangle colliderRight;
    bool isHandEmpty;
    bool isJumping;
    bool hitObstacle;
    bool hitLeft;
    bool hitRight;
    Vector2 velocity;
    float maxY;
    int hearts;
    int points;
} Player;

void initPlayer(Player *player, int screenWidth, int screenHeight);
void updatePlayer(Player *player, float deltaTime, int map[MAX_ROWS][MAX_COLS], Camera2D camera);
void drawPlayer(Player *player, Camera2D camera);
void unloadPlayer(Player *player);

#endif  // PLAYER_H
