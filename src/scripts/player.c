
#include "coffeeSeed.h"

#include "coffeeSeedManager.h"
#include "player.h"
#include "animation.c"
#include "animation.h"
#include <stdio.h>  // Include necessary headers as needed

int tmpPoints = 0;
int xdScene = 0;

void initPlayer(Player *player, int screenWidth, int screenHeight) {
    // Initialization code for the player
    player->position.x = screenWidth / 2;
    player->position.y = 768;
    player->speed = PLAYER_SPEED;
    player->collider = (Rectangle){ player->position.x, player->position.y, 64, 64 };
    player->colliderDown = (Rectangle){ player->position.x + 20, player->position.y + LOWER_COLLIDER_OFFSET, 28, 8 };
    player->colliderUp = (Rectangle){ player->position.x + 20, player->position.y, 28, 8 };
    player->colliderLeft = (Rectangle){ player->position.x, player->position.y, 8, 60 };
    player->colliderRight = (Rectangle){ player->position.x + RIGHT_COLLIDER_OFFSET, player->position.y, 8, 60 };
    player->hearts = 1;
    player->maxY = player->position.y;
    player->hitLeft = false;
    player->hitRight = false;
    player->isHandEmpty = true;
    player->hitObstacle = false;
    player->isJumping = false;
    player->points = 0;
    //player->texture = LoadTexture("src/textures/player.png");
    player->walkAnimation.texture = LoadTexture("src/textures/player.png");
    player->walkAnimation.frameCount = 2; // Number of frames in the walk animation
    player->walkAnimation.currentFrame = 0;
    player->walkAnimation.frameTime = 0.1f; // Time between frames (adjust as needed)
    player->walkAnimation.currentTime = 0.0f;
    
    
        // Calculate frames within the texture atlas for walk animation
    // Modify this based on your texture atlas layout
    // Assuming each frame is 64x64 pixels
    player->walkAnimation.frames = (Rectangle*)malloc(player->walkAnimation.frameCount * sizeof(Rectangle));
    int frameWidth = 32;
    int frameHeight = 32;
    for (int i = 0; i < player->walkAnimation.frameCount; i++) {
        player->walkAnimation.frames[i].x = i * frameWidth;
        player->walkAnimation.frames[i].y = 0; // Assuming frames are on the first row
        player->walkAnimation.frames[i].width = frameWidth;
        player->walkAnimation.frames[i].height = frameHeight;
    }
}

void updatePlayer(Player *player, float deltaTime, int map[MAX_ROWS][MAX_COLS], Camera2D camera, Sound jumpSound, Sound hurtSound, Sound pickupSound) {
    float speedPerSecond = player->speed * deltaTime;
    //const float speedPerSecond = 5.0f;
    checkCollisionLeft(player, map, deltaTime);
    checkCollisionRight(player, map, deltaTime);
     
   
    
    
    if (IsKeyDown('S')){
        speedPerSecond = 1.4 * player->speed * deltaTime;
    } else {
        speedPerSecond = player->speed * deltaTime;
    }
    // Handle player input for horizontal movement
    if (IsKeyDown(KEY_RIGHT)) {
        if(player->hitRight == false){
            player->walkAnimation.frames[0].width = 32;
            player->walkAnimation.frames[1].width = 32;
            player->position.x += speedPerSecond;
            if(!player->isJumping) updateAnimation(&player->walkAnimation, deltaTime);
        }
    } else if (IsKeyDown(KEY_LEFT) && player->position.x > camera.target.x - GetScreenWidth()/2 && player->hitLeft == false) {
        player->walkAnimation.frames[0].width = -32;
        player->walkAnimation.frames[1].width = -32;
        player->position.x -= speedPerSecond;
        if(!player->isJumping) updateAnimation(&player->walkAnimation, deltaTime);

    }
    
    
    
    player->hitLeft = false;
    player->hitRight = false;
    player->hitObstacle = false;
    //checkPlayerCollisionWithMap(player, map, deltaTime);
    checkCollisionDown(player, map, deltaTime);
    checkCollisionUp(player, map, deltaTime, camera);
    if(xdScene == 2) PlaySound(hurtSound);
    //checkCollisionWithCoffe();
    
    // Handle player input for jumping
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) {
        // Only allow jumping if the player is not already jumping
        if (!player->isJumping) {
            // Apply upward velocity for jumping
            player->velocity.y = -JUMP_FORCE;
            player->isJumping = true;
            player-> hitObstacle = false;
            PlaySound(jumpSound);
        }
    }
    
    

    // Apply gravity to the player
    if(player->points > tmpPoints){
    PlaySound(pickupSound);
    tmpPoints = player->points;
    }
  
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
    player->collider.x = player->position.x + 1;
    player->collider.y = player->position.y;
    
    player->colliderUp.x = player->position.x + 12;
    player->colliderUp.y = player->position.y + LOWER_COLLIDER_OFFSET;
    
    player->colliderDown.x = player->position.x + 12 ;
    player->colliderDown.y = player->position.y;
    
    player->colliderLeft.x = player->position.x + 9;
    player->colliderLeft.y = player->position.y + 2;
    
    player->colliderRight.x = player->position.x + RIGHT_COLLIDER_OFFSET;
    player->colliderRight.y = player->position.y + 2;
        
}

void checkCollisionUp(Player *player, int map[MAX_ROWS][MAX_COLS], Camera2D camera) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            float tileX = col * 64;
            float tileY = row * 64;

            if (CheckCollisionRecs(player->colliderUp, (Rectangle){ tileX, tileY, 64, 64 })) {
                
                if (map[row][col] == 9 || map[row][col] == 8) {
                    // Change the scene to 2
                    //printf("Transitioning to scene 2 (death screen)\n");
                    
                    xdScene = 2;
                     
                } //else xdScene = 0;
                
                if (map[row][col] == 6) {
                    // Change the scene to 2
                    //printf("Transitioning to scene 2 (death screen)\n");
                    
                    xdScene = 3;
                     
                } //else xdScene = 0;
                
                if(map[row][col] == 3 && IsKeyDown('A')){
                    map[row][col] = 0;
                    player->velocity.y -= BREAK_BOUNCE;
                    player->points += 5;
                    //spawnCoffeeSeed(&coffeeSeedManager->coffeeSeed[coffeeSeedManager->numSeeds], (Vector2){200, 750}, camera);
                    //coffeeSeedManager->numSeeds++;

                    
                    
                }
                 if(map[row][col] != 0  && map[row][col] != 7){
                    player->isJumping = false;
                    player->hitObstacle = true;
                    player->velocity.y = 0;
                    float overlapY = player->position.y + 64 - tileY;

                    // Adjust the player's position to prevent overlap
                    player->position.y -= overlapY;
                }
            }
        }
    }
}

// Function to check collision with tiles below the player
void checkCollisionDown(Player *player, int map[MAX_ROWS][MAX_COLS]) {
    
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            float tileX = col * 64;
            float tileY = row * 64;

            if (CheckCollisionRecs(player->colliderDown, (Rectangle){ tileX, tileY, 64, 64 })) {
                
                if(map[row][col] == 3){
                    map[row][col] = 0;
                    player->velocity.y += BREAK_BOUNCE;
                    player->points += 5;
                    
                }
                if(map[row][col] != 0){
                    player->velocity.y = 0;
                    
                    float overlapY = tileY + 64 - player->position.y;

                    // Adjust the player's position to prevent overlap
                    player->position.y += overlapY;
                }
                
            } 
        }
    }
}

// Function to check collision with tiles to the left of the player
void checkCollisionLeft(Player *player, int map[MAX_ROWS][MAX_COLS]) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            float tileX = col * 64;
            float tileY = row * 64;

            if (CheckCollisionRecs(player->colliderLeft, (Rectangle){ tileX, tileY, 64, 64 })) {
                if(map[row][col] != 0  && map[row][col] != 7){
                    player->hitLeft = true;
                } 
            }
        }
    }
}

// Function to check collision with tiles to the right of the player
void checkCollisionRight(Player *player, int map[MAX_ROWS][MAX_COLS]) {
   
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            float tileX = col * 64;
            float tileY = row * 64;

            if (CheckCollisionRecs(player->colliderRight, (Rectangle){ tileX, tileY, 64, 64 })) {
                if(map[row][col] != 0 && map[row][col] != 7){
                    player->hitRight = true;
                    
                }
            }
        }
    }
}
void drawPlayer(Player *player, Camera2D camera) {
    BeginMode2D(camera);
    
    // Define source and destination rectangles for scaling
    //Rectangle sourceRect = { 0, 0, player->texture.width, player->texture.height }; // Source rectangle is the entire texture
    //Rectangle destRect = { player->position.x, player->position.y, 64, 64 }; // Destination rectangle is 64x64
    
    // Draw the texture with scaling using DrawTexturePro
    //DrawTexturePro(player->texture, sourceRect, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    
    
    
    
     // Draw the current frame of the walk animation
    Rectangle sourceRect = player->walkAnimation.frames[player->walkAnimation.currentFrame];
    Rectangle destRect = { player->position.x, player->position.y, 64, 64 };
    DrawTexturePro(player->walkAnimation.texture, sourceRect, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

    
    // Draw player collider
    //DrawRectangleLinesEx(player->colliderUp, 1, RED);
    //DrawRectangleLinesEx(player->colliderDown, 1, GREEN);
    //DrawRectangleLinesEx(player->colliderLeft, 1, BLUE);
    //DrawRectangleLinesEx(player->colliderRight, 1, BLACK);
    
    EndMode2D();
}
int sceneCheck(){
    if(xdScene == 0) return 1;
    if(xdScene == 1) return 2;
    if(xdScene == 2) return 2;
    if(xdScene == 3) return 3;
}
void resetScene(){
    xdScene = 0;
}
void unloadPlayer(Player *player) {
    // Unload resources (textures, etc.) used by the player
    UnloadTexture(player->texture);
}
