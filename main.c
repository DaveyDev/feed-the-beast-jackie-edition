#include "raylib.h"

const char *title = "PROJECT JACKIE - MENU";
const int titleFontSize = 48;


int main(void)
{

    
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "PROJECT JACKIE TEST");

    SetTargetFPS(60); 



    while (!WindowShouldClose())
    {
        

        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
                // Measure the width of the text
            int titleWidth = MeasureText(title, titleFontSize);
            int titlePosX = (GetScreenWidth() - titleWidth) / 2;

            DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, BLACK);

        EndDrawing();

    }


    CloseWindow();        // Close window and OpenGL context


    return 0;
}