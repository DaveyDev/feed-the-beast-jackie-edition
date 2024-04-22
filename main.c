#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#include "src/scripts/constants.h"

#include "src/scripts/player.c"
#include "src/scripts/hoe.c"
#include "src/scripts/checkCollision.c"
#include "src/scripts/menu.c"
#include "src/scripts/waterCan.c"
#include "src/scripts/coffeeSeed.c"
#include "src/scripts/textures.c"
#include "src/scripts/map.c"
#include "src/scripts/plant.c"
#include "src/scripts/shop.c"
//#include "src/scripts/cameraFollow.c"



//Vector2 target = { 0 };


int main() {
    // Load the map from the text file
    loadMap("src/map.txt");
    int scene = 0;
    //int numSeeds = 0;
    
    int coins = 0;
    
    // Raylib Initialization
    const int screenWidth = 832;
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "Feed the Beast: Jackie Edition");
    
    loadTextures();
    
    
    Player player;
    initPlayer(&player, screenWidth, screenHeight - 100, 213.7f); // Initial position and speed
    
    //Vector2 cameraPosition = updateCameraFollow();
        
    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    Hoe hoe;
    spawnHoe(&hoe, (Vector2){200, 300});
    
    WaterCan waterCan;
    spawnWaterCan(&waterCan, (Vector2){300, 200});
    
    Shop shop;
    spawnShop(&shop, (Vector2){200, 50});
    
    CoffeeSeed coffeeSeed;
    CoffeeSeedManager coffeeSeedManager = {0};
    
    CoffeePlant coffeePlant;
    CoffeePlantManager coffeePlantManager = {0};
    
    
    spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){100, 300});
    coffeeSeedManager.numSeeds++;
    spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){100, 350});
    coffeeSeedManager.numSeeds++;
    
    



    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
   


        if(scene == 0){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //ameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        

        
         // Set the camera position
        drawMap(camera);
        scene = menuScene();

        
        }
        
        if(scene != 0){
            
            
            float deltaTime = GetFrameTime();
            updatePlayer(&player, deltaTime, map);
            //camera.zoom += ((float)GetMouseWheelMove()*0.05f);
           
            
            
            camera.target.x = player.position.x; // Update the camera's target to follow the player

            BeginMode2D(camera);
            
            updateCameraCenter(&camera, &player, deltaTime,screenWidth, screenHeight);
            
        if (checkCollision(player.collider, hoe.collider) && IsKeyDown(KEY_E) && player.isHandEmpty) {
            
            hoe.isActive = false;
            hoe.isEquipped = true;
            player.isHandEmpty = false;// Mark hoe as inactive (picked up)
            // Perform actions associated with picking up the hoe (e.g., increase score)
        }
        if (checkCollision(player.collider, waterCan.collider) && IsKeyDown(KEY_E) && player.isHandEmpty) {
            
            waterCan.isActive = false;
            waterCan.isEquipped = true;
            player.isHandEmpty = false;// Mark hoe as inactive (picked up)
            // Perform actions associated with picking up the hoe (e.g., increase score)
        }

        if(hoe.isEquipped && IsKeyDown(KEY_Q)){
            
            hoe.isActive = true;
            hoe.isEquipped = false;
            hoe.position.x = player.position.x;
            hoe.collider.x = player.position.x;
            hoe.position.y = player.position.y;
            hoe.collider.y = player.position.y;
            
            player.isHandEmpty = true;
        }
        if(waterCan.isEquipped && IsKeyDown(KEY_Q)){
            
            waterCan.isActive = true;
            waterCan.isEquipped = false;
            waterCan.position.x = player.position.x;
            waterCan.collider.x = player.position.x;
            waterCan.position.y = player.position.y;
            waterCan.collider.y = player.position.y;
            
            player.isHandEmpty = true;
        }

        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
          
        clickOnTile(&player, &hoe, &waterCan);
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the map
        updateMap(&coffeeSeedManager);
        
        drawMap(camera);
        
       
   
        DrawTexture(emptyHand, 0, 0, WHITE);
        
        //Draw hoe  
        //updateHoe(&hoe);
        drawHoe(&hoe);
        drawWaterCan(&waterCan);
        
        
        drawShop(&shop);
        
        for (int i = 0; i < coffeeSeedManager.numSeeds; i++) {
            CoffeeSeed *coffeeSeed = &coffeeSeedManager.coffeeSeed[i];
        if(checkCollision(shop.collider, coffeeSeed->collider)){
            coffeeSeed->isActive = false;
            coffeeSeed->collider.x = 1000;
            coffeeSeed->collider.y = 1000;
            coins++;
            
        }}
        
        //draw plants
        
        
        
        
        
        interactWithCoffeePlants(&player, &coffeePlantManager, map, lastChangeTimes);
        drawCoffeePlant(&coffeePlantManager);
        
        drawCoffeeSeed(&coffeeSeedManager);
        interactWithCoffeeSeeds(&player, &coffeeSeedManager);
        
        
        
        
        //float deltaTime = GetFrameTime();
        
        
        //target = player.position;
        //cameraPosition = updateCameraFollow();

      
        drawPlayer(&player);
        EndMode2D();
        
        DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
        DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);
        
        int countFPS = GetFPS();
        DrawText(TextFormat("FPS: %i", countFPS), screenWidth - 100, 15, 20, BLUE);
        DrawText(TextFormat("ver. 240126"), screenWidth - 150, 600, 20, BLUE);
        DrawText(TextFormat("coins: %i", coins), 80, 15, 20, BLUE);
        
        }
     
        
        EndDrawing();
        
    }
    
    unloadPlayer(&player);
    unloadHoe(&hoe);
    unloadWaterCan(&waterCan);
    unloadCoffeeSeeds(&coffeeSeed);
    unloadShop(&shop);
    unloadTextures();
    CloseWindow();

    return 0;
}

void updateCameraCenter(Camera2D *camera, Player *player, float delta, int width, int height)
{
    // Update the camera's offset based on zoom level and screen dimensions
    camera->offset.x = width / (2.0f * camera->zoom);
    camera->offset.y = height / (2.0f * camera->zoom);

    // Calculate the camera's position relative to the target
    camera->target.x = player->position.x;
    camera->target.y = player->position.y;
}





