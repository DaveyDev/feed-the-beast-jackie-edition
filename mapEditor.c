#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
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




int main() {
    // Load the map from the text file
    loadMap("src/map.txt");
    
    // Raylib Initialization 
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int keyNo;
    InitWindow(screenWidth, screenHeight, "Map Editor");
    
    loadTextures();
    
    Camera2D camera = { 0 };
    camera.target.y = screenHeight/2 - 20;
    //camera.target.y = player.position.y - 100;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    
   
   
    ToggleFullscreen();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        if (IsKeyDown(KEY_A)) {
            camera.target.x -= 10;
        }
        if (IsKeyDown(KEY_D)) {
            camera.target.x += 10;
        }
        
        if(IsKeyPressed(KEY_ONE)) keyNo = 1;
        if(IsKeyPressed(KEY_TWO)) keyNo = 2;
        if(IsKeyPressed(KEY_THREE)) keyNo = 3;
        if(IsKeyPressed(KEY_FOUR)) keyNo = 4;
        if(IsKeyPressed(KEY_FIVE)) keyNo = 5;
        if(IsKeyPressed(KEY_SIX)) keyNo = 6;
        if(IsKeyPressed(KEY_SEVEN)) keyNo = 7;
        if(IsKeyPressed(KEY_EIGHT)) keyNo = 8;
        if(IsKeyPressed(KEY_NINE)) keyNo = 9;
        if(IsKeyPressed(KEY_ZERO)) keyNo = 0;
     
        //if(scene == 0){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawMap(camera);
        
            Vector2 mousePos = GetMousePosition();
    Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);

    // Convert world position to screen coordinates for drawing text
    Vector2 textPos = { 20, 20 }; // Position for displaying cursor coordinates

    // Draw cursor position text
    DrawText(TextFormat("Mouse Position: (%.0f, %.0f)", worldPos.x, worldPos.y), (int)textPos.x, (int)textPos.y + 30, 20, BLACK);
    DrawText(TextFormat("Mouse Position: (%.0f, %.0f)", worldPos.x, worldPos.y), (int)textPos.x, (int)textPos.y, 20, WHITE);
        
        
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) clickOnTileMapEditor(camera, keyNo);
       
        
        
        EndDrawing();
        
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }
        
        }
    
    saveMap("src/map.txt");
    unloadTextures();
    CloseWindow();

    return 0;
}

void saveMap(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        exit(EXIT_FAILURE);
    }

    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            fprintf(file, "%d ", map[row][col]);
        }
        fprintf(file, "\n"); // Add a newline after each row
    }

    fclose(file);
}


void clickOnTileMapEditor(Camera2D camera, int keyNo) {
    Vector2 mousePos = GetMousePosition();
    
    // Convert mouse position to world coordinates using camera
    Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
    
    // Calculate map indices based on world coordinates
    int col = (int)(worldPos.x / 64);
    int row = (int)(worldPos.y / 64);
    
    // Check if the calculated indices are within bounds
    if (row >= 0 && row < MAX_ROWS && col >= 0 && col < MAX_COLS) {
        // Toggle tile value
        if(keyNo == 1){
            map[row][col] = 1;
        } else if (keyNo == 2) {
            map[row][col] = 2;
        } else if (keyNo == 3) {
            map[row][col] = 3;
        } else if (keyNo == 4) {
            map[row][col] = 4;
        } else if (keyNo == 5) {
            map[row][col] = 5;
        } else if (keyNo == 6) {
            map[row][col] = 6;
        } else if (keyNo == 7) {
            map[row][col] = 7;
        } else if (keyNo == 8) {
            map[row][col] = 8;
        } else if (keyNo == 9) {
            map[row][col] = 9;
        } else if (keyNo == 0) {
            map[row][col] = 0;
        } 
    }
}
