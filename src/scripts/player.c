#include "constants.h"
#include <math.h>

   
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
    
} Player;

void initPlayer(Player *player, int screenWidth, int screenHeight, float speed) {
    player-> position.x = screenWidth/2;
    player-> position.y = screenHeight/2;
    player-> speed = speed;
    player-> collider  = (Rectangle){player-> position.x, player->position.y, 64, 64};
    player-> colliderDown  = (Rectangle){player-> position.x, player->position.y + LOWER_COLLIDER_OFFSET, 64, 8};
    //player-> collider  = (Rectangle){player-> position.x, player->position.y, 64, 64};
    player-> colliderUp  = (Rectangle){player-> position.x, player->position.y, 64, 8};
    player-> colliderLeft  = (Rectangle){player-> position.x, player->position.y, 8, 64};
    player-> colliderRight  = (Rectangle){player-> position.x + RIGHT_COLLIDER_OFFSET, player->position.y, 8, 64};
    
    
    
    player-> isHandEmpty = true;
    player-> hitObstacle = false;
    player-> isJumping = false;
    
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
}*/

void updatePlayer(Player *player, float deltaTime, int map[MAX_ROWS][MAX_COLS], Camera2D camera) {
    float speedPerSecond = player->speed * deltaTime;
    //const float speedPerSecond = 5.0f;

    // Handle player input for horizontal movement
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D') && player->hitRight == false) {
        player->position.x += speedPerSecond;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown('A') && player->position.x > camera.target.x -320 && player->hitLeft == false) {
        player->position.x -= speedPerSecond;
    }
    
    player->hitObstacle = false;
    checkPlayerCollisionWithMap(player, map, deltaTime);
    //checkCollisionWithCoffe();
    
    // Handle player input for jumping
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown('W')) {
        // Only allow jumping if the player is not already jumping
        if (!player->isJumping) {
            // Apply upward velocity for jumping
            player->velocity.y = -JUMP_FORCE;
            player->isJumping = true;
            player-> hitObstacle = false;
        }
    }
    

    // Apply gravity to the player
    
  
    if(!player->hitObstacle){
    player->velocity.y += GRAVITY * deltaTime;
    
    // Update player's vertical position based on velocity
    player->position.y += player->velocity.y * deltaTime;
    }

    // Check for collisions with the ground (grass)
    //if (checkCollisionWithGrass(player, map)) {
        // If the player is colliding with the ground, stop the jump and reset vertical position
       // player->isJumping = false;
        
       //player->velocity.y = 0;
   // }

    // Update player's collider position
    player->collider.x = player->position.x;
    player->collider.y = player->position.y;
    
    player->colliderUp.x = player->position.x;
    player->colliderUp.y = player->position.y + LOWER_COLLIDER_OFFSET;
    
    player->colliderDown.x = player->position.x;
    player->colliderDown.y = player->position.y;
    
    player->colliderLeft.x = player->position.x;
    player->colliderLeft.y = player->position.y;
    
    player->colliderRight.x = player->position.x + RIGHT_COLLIDER_OFFSET;
    player->colliderRight.y = player->position.y;
        
}

void checkPlayerCollisionWithMap(Player *player, int map[MAX_ROWS][MAX_COLS], float deltaTime) {
    // Iterate through map tiles
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            // Calculate position of map tile
            float tileX = col * 64;
            float tileY = row * 64;

            // Check collision between player and map tile
            if (CheckCollisionRecs(player->colliderUp, (Rectangle){ tileX, tileY, 64, 64 })) {
               // printf("Velocity.y: %f\n", player->velocity.y);
                if(map[row][col] != 0){
                    player->isJumping = false;
                    player->hitObstacle = true;
                    player->velocity.y = 0;
                    
                    //if(player->collider.y < tileY){
                       // player->velocity.y -= tileY - player->collider.y;
                    //}
                 
                }
                
             
                
                // Handle collision
                // For example, stop player movement or adjust player position
                // You can also add specific actions based on the type of tile collided with
                // For instance, if it's a wall tile, prevent the player from moving through it
            }
            if(CheckCollisionRecs(player->colliderDown, (Rectangle){tileX, tileY, 64, 64})){
                if(map[row][col] != 0){
                   
                    player->velocity.y = 0;
                   
                 
                }
            }
            if(CheckCollisionRecs(player->colliderLeft, (Rectangle){tileX, tileY, 64, 64})){
                if(map[row][col] != 0){
                   
                    player->hitLeft = true;
                   
                 
                } else {
                    player->hitLeft = false;
                }
            }
            if(CheckCollisionRecs(player->colliderRight, (Rectangle){tileX, tileY, 64, 64})){
                if(map[row][col] != 0){
                   
                    player->hitRight = true;
                   
                 
                } else { 
                    player->hitRight = false;
                }
            }
            
            }
        }
    }
/*
void checkPlayerCollisionWithMap(Player *player, int map[MAX_ROWS][MAX_COLS], float deltaTime) {
    // Iterate through map tiles
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            // Calculate position of map tile
            float tileX = col * 64;
            float tileY = row * 64;

            // Check collision between player and map tile
            if (CheckCollisionRecs(player->collider, (Rectangle){ tileX, tileY, 64, 64 })) {
                if(map[row][col] != 0){
                    // Determine the direction of collision (top, bottom, left, or right)
                    float overlapX = player->collider.x + player->collider.width / 2 - tileX;
                    float overlapY = player->collider.y + player->collider.height / 2 - tileY;
                    float overlapWidth = player->collider.width / 2 + 32 - fabsf(overlapX);
                    float overlapHeight = player->collider.height / 2 + 32 - fabsf(overlapY);
                    
                    // Resolve collision based on the direction
                    if (overlapWidth < overlapHeight) {
                        // Collided from left or right
                        if (overlapX > 0)
                            player->position.x += overlapWidth;
                        else
                            player->position.x -= overlapWidth;
                    } else {
                        // Collided from top or bottom
                        if (overlapY > 0) {
                            player->position.y += overlapHeight;
                            // Stop jumping when hitting the bottom of the block
                            player->isJumping = false;
                            player->velocity.y = 0;
                        } else {
                            player->position.y -= overlapHeight;
                            // Reverse velocity when hitting the top of the block (optional)
                            // player->velocity.y = -player->velocity.y;
                        }
                    }
                }
            }
        }
    }
}*/






void drawPlayer(Player *player, Camera2D camera) {
    BeginMode2D(camera);
    
    // Define source and destination rectangles for scaling
    Rectangle sourceRect = { 0, 0, player->texture.width, player->texture.height }; // Source rectangle is the entire texture
    Rectangle destRect = { player->position.x, player->position.y, 64, 64 }; // Destination rectangle is 64x64
    
    // Draw the texture with scaling using DrawTexturePro
    DrawTexturePro(player->texture, sourceRect, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    
    // Draw player collider
    DrawRectangleLinesEx(player->colliderUp, 1, RED);
    DrawRectangleLinesEx(player->colliderDown, 1, GREEN);
    DrawRectangleLinesEx(player->colliderLeft, 1, BLUE);
    DrawRectangleLinesEx(player->colliderRight, 1, BLACK);
    
    EndMode2D();
}


void unloadPlayer(Player *player) {
    UnloadTexture(player->texture);
}
