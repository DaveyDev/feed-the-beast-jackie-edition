#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#include "src/scripts/constants.h"
#include "src/scripts/coffeeSeedManager.h"
#include "src/scripts/coffeeSeed.h"
#include "src/scripts/player.h"


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

int scene = 0;

//Vector2 target = { 0 };


int main() {
    // Load the map from the text file
    loadMap("src/map.txt");
    
    int test = 0;
    //int numSeeds = 0;
    InitAudioDevice();
    Sound jumpSound = LoadSound("src/sounds/jump.wav");    
    Sound hurtSound = LoadSound("src/sounds/hitHurt.wav");  
    Sound pickupSound = LoadSound("src/sounds/pickupCoin.wav");  
    //Sound jumpSound = LoadSound("src/sounds/jump.wav");  

    int coins = 0;
    
    // Raylib Initialization
    const int screenWidth = 832;
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "Feed the Beast: Jackie Edition");
    
    loadTextures();
    
    
    Player player;
    //initPlayer(&player, screenWidth, screenHeight  - 100); // Initial position and speed
    
    //Vector2 cameraPosition = updateCameraFollow();
        
    Camera2D camera = { 0 };
    //camera.target.x = player.position.x;
    //camera.target.y = player.position.y - 100;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    
    
    Hoe hoe;
    //spawnHoe(&hoe, (Vector2){200, 300});
    
    WaterCan waterCan;
    //spawnWaterCan(&waterCan, (Vector2){300, 200});
    
    Shop shop;
    //spawnShop(&shop, (Vector2){200, 50});
    
    CoffeeSeed coffeeSeed;
    CoffeeSeedManager coffeeSeedManager = {0};
    
    CoffeePlant coffeePlant;
    CoffeePlantManager coffeePlantManager = {0};
    
    
    //spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){100, 300});
    //coffeeSeedManager.numSeeds++;
    
    


    
    



    SetTargetFPS(60);  

    while (!WindowShouldClose()) {
        


    switch(scene){
    case 0:
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        //initPlayer(&player, screenWidth, screenHeight  - 100);
        //ameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        if(test == 0){
            initPlayer(&player, screenWidth, screenHeight  - 100);
            camera.target.x = player.position.x;
            
            camera.target.y = player.position.y - 100;
            
            loadMap("src/map.txt");
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){545, 805}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){760, 300}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){1640, 420}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){2615, 265}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){4310, 540}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){5330, 220}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){6170, 825}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7330, 300}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7390, 300}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7450, 300}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7490, 300}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7390, 250}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7450, 250}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7450, 250}, camera);
            coffeeSeedManager.numSeeds++;
            spawnCoffeeSeed(&coffeeSeedManager.coffeeSeed[coffeeSeedManager.numSeeds], (Vector2){7490, 250}, camera);
            coffeeSeedManager.numSeeds++;
    
            
            
            
            test++;
        }
    // Set the camera position
        //drawMap(camera);
        scene = menuScene();

        
    break;
        
    case 1:
            
            
            float deltaTime = GetFrameTime();
            updatePlayer(&player, deltaTime, map, camera, jumpSound, hurtSound, pickupSound);
            //camera.zoom += ((float)GetMouseWheelMove()*0.05f);
           
            
            
            //camera.target.x = player.position.x; // Update the camera's target to follow the player

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

        /*
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
          
        clickOnTile(&player, &hoe, &waterCan);
        }*/
        
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Draw the map
        //updateMap(&coffeeSeedManager);
        
        drawMap(camera);
        
       
   
        //DrawTexture(emptyHand, 0, 0, WHITE);
        
        //Draw hoe  
        //updateHoe(&hoe);
        drawHoe(&hoe);
        drawWaterCan(&waterCan);
        
        
        drawShop(&shop);
        
        for (int i = 0; i < coffeeSeedManager.numSeeds; i++) {
            CoffeeSeed *coffeeSeed = &coffeeSeedManager.coffeeSeed[i];
        if(checkCollision(shop.collider, coffeeSeed->collider)){
            coffeeSeed->isActive = false;
            if(checkCollision(coffeeSeed->collider, player.collider)){
            coins++;
            }
            
        }}
        
        //draw plants
        
        
        
        
        
        interactWithCoffeePlants(&player, &coffeePlantManager, map, lastChangeTimes);
        drawCoffeePlant(&coffeePlantManager);
        
        drawCoffeeSeeds(&coffeeSeedManager, camera);
        interactWithCoffeeSeeds(&player, &coffeeSeedManager);
        
        
        
        
        //float deltaTime = GetFrameTime();
        
        
        //target = player.position;
        //cameraPosition = updateCameraFollow();

      
        drawPlayer(&player, camera);
        
        EndMode2D();
        
        //DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
        //DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);
        
        int countFPS = GetFPS();
        DrawText(TextFormat("FPS: %i", countFPS), screenWidth - 100, 15, 20, WHITE);
        DrawText(TextFormat("ver. a240427"), screenWidth - 150, 600, 20, WHITE);
        DrawText(TextFormat("coffee: %i", player.points), 20, 15, 20, WHITE);
        
        
    break;
    
    case 2:
    
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //ameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        
        // Set the camera position
        //drawMap(camera);
        test = 0;
        scene = deathScene();
    
    
        break;
        
    case 3:
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //ameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        
        // Set the camera position
        //drawMap(camera);
        test = 0;
        scene = winScene(&player);
        
    }
    if(scene == 1 || scene == 2 || scene == 3){
    scene = sceneCheck();
    test = 0;
    }
    //printf("Current Scene: %d\n", scene);
        
        EndDrawing();
        
    }
    
    unloadPlayer(&player);
    unloadHoe(&hoe);
    unloadWaterCan(&waterCan);
    unloadCoffeeSeeds(&coffeeSeed);
    unloadShop(&shop);
    unloadTextures();
    UnloadSound(jumpSound);
    UnloadSound(hurtSound);
    UnloadSound(pickupSound);
    CloseWindow();

    return 0;
}

void updateCameraCenter(Camera2D *camera, Player *player, float delta, int width, int height)
{
    camera->offset = (Vector2){ width/2.0f, height/2.0f - 48 };
    if(camera->target.x < player->position.x){
    camera->target.x = player->position.x;
    }
    if(player->position.y < 650 && player->position.y > 200){
    camera->target.y = player->position.y;
    }
}





