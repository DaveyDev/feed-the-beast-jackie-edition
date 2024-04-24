
Vector2 mousePoint = {};
Color buttonColor = (Color){0, 0, 0, 50};
Color noColor = (Color){0, 0, 0, 0};


Rectangle playButton = {832/2 - 100, 640/2, 200, 50};


int menuScene(){
    
    mousePoint = GetMousePosition();
    
    
    Color bgColor = (Color){0, 200, 100, 255};
    ClearBackground(bgColor);
    
    
    if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    else DrawRectangleRec(playButton, noColor);
    


    DrawText("JACKIE MAKES COFFEE", GetScreenWidth()/2 - 250, GetScreenHeight()/2 - 150, 40, WHITE);
    DrawText("PLAY", GetScreenWidth()/2 - 40, GetScreenHeight()/2 + 12, 30, WHITE);
    
    if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;  
    
    
    return 0;
}