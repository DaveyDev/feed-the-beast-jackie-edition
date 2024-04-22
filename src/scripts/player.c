#include "constrants.h"
#include <math.h>

   
typedef struct {
    Vector2 position;
    Texture2D texture;
    float speed;
    Rectangle collider;
    bool isHandEmpty;
    bool isJumping;
    Vector2 velocity;
    
} Player;

void initPlayer(Player *player, int screenWidth, int screenHeight, float speed) {
    player-> position.x = screenWidth/2;
    player-> position.y = screenHeight/2;
    player-> speed = speed;
    player-> collider  = (Rectangle){player-> position.x, player->position.y, 64, 64};
    
    player-> isHandEmpty = true;
    player-> texture = LoadTexture("src/textures/player.png");
    
}

bool checkCollisionWithGrass(Player *player, int map[MAX_ROWS][MAX_COLS]) {
    // Iterate over the map
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            // Check if the current block is grass (value 1)
            if (map[row][col] == 1) {
                // Calculate the position of the current grass block
                float grassX = col * 64;
                float grassY = row * 64;
                // Check for collision between player and grass block
                if (CheckCollisionRecs(player->collider, (Rectangle){grassX, grassY, 64, 64})) {
                    // Collision detected with grass block
                    return true;
                }
            }
        }
    }
    // No collision detected with grass blocks
    return false;
}

/*
void updatePlayer(Player *player, float deltaTime, int map[MAX_ROWS][MAX_COLS]) {
    float speedPerSecond = player->speed * deltaTime;
    // Handle player input (e.g., arrow keys or WASD)
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D') && player-> position.x < GetScreenWidth() - 32) {
        player-> position.x += speedPerSecond;
        
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown('A') && player-> position.x > -32) {
        player->position.x -= speedPerSecond;
        
    }

    if (!checkCollisionWithGrass(player, map) && player-> position.y < GetScreenHeight() - 32) {
        player->position.y += speedPerSecond;
        
    } else if (IsKeyDown(KEY_UP) || IsKeyDown('W') && player-> position.y > -32) {
        player->position.y -= speedPerSecond;
        
    }
    
    player-> collider.x = player-> position.x;
    player-> collider.y = player-> position.y;
}
*/
void updatePlayer(Player *player, float deltaTime, int map[MAX_ROWS][MAX_COLS]) {
    float speedPerSecond = player->speed * deltaTime;

    // Handle player input for horizontal movement
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D') && player->position.x < GetScreenWidth() - 32) {
        player->position.x += speedPerSecond;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown('A') && player->position.x > -32) {
        player->position.x -= speedPerSecond;
    }
    

    // Handle player input for jumping
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown('W')) {
        // Only allow jumping if the player is not already jumping
        if (!player->isJumping) {
            // Apply upward velocity for jumping
            player->velocity.y = -JUMP_FORCE;
            player->isJumping = true;
        }
    }
    

    // Apply gravity to the player
    player->velocity.y += GRAVITY * deltaTime;

    // Update player's vertical position based on velocity
    player->position.y += player->velocity.y * deltaTime;

    // Check for collisions with the ground (grass)
    if (checkCollisionWithGrass(player, map)) {
        // If the player is colliding with the ground, stop the jump and reset vertical position
        player->isJumping = false;
        player->position.y = floor(player->position.y / 64) * 64;
        player->velocity.y = 0;
    }

    // Update player's collider position
    player->collider.x = player->position.x;
    player->collider.y = player->position.y;
}




void drawPlayer(Player *player) {
    
    DrawTexture(player->texture, player->position.x, player->position.y, WHITE);
}

void unloadPlayer(Player *player) {
    UnloadTexture(player->texture);
}