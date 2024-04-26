
Vector2 mousePoint = {};
Color buttonColor = (Color){0, 0, 0, 50};
Color noColor = (Color){0, 0, 0, 0};


Rectangle playButton = {832/2 - 100, 640/2, 200, 50};

const char *title = "FEED THE BEAST";
const int titleFontSize = 48;
const char *subtitle = "JACKIE EDITION";
const int subtitleFontSize = 40;
char *playBtn = "UwU";
const int playBtnFontSize = 30;


const char *subtitleDeath = "YOU DEAD";
const int subtitleDeathFontSize = 40;
const char *mainMenuBtn = "Main Menu";
const int mainMenuBtnFontSize = 30;

const char *subtitleWin = "YOU WIN";
const int subtitleWinFontSize = 40;

int menuScene(){
    
    mousePoint = GetMousePosition();
    
    
    Color bgColor = (Color){0, 200, 100, 255};
    ClearBackground(bgColor);
    
    
    if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    else DrawRectangleRec(playButton, noColor);
    
    // Measure the width of the text
    int titleWidth = MeasureText(title, titleFontSize);
    int titlePosX = (GetScreenWidth() - titleWidth) / 2;
    
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
    int subtitlePosX = (GetScreenWidth() - subtitleWidth) / 2;
    
    int playBtnWidth = MeasureText(playBtn, playBtnFontSize);
    int playBtnPosX = (GetScreenWidth() - playBtnWidth) / 2;
    
    DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, WHITE);
    DrawText(subtitle, subtitlePosX, GetScreenHeight()/2 - 100, subtitleFontSize, WHITE);
    DrawText(playBtn, playBtnPosX, GetScreenHeight()/2 + 12, playBtnFontSize, WHITE);
    
    if (CheckCollisionPointRec(mousePoint, playButton)){
        playBtn = ">w<";
    } else {
        playBtn = "UwU";
    }
    if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;  
    
    
    return 0;
}

int deathScene(){
    
    mousePoint = GetMousePosition();
    
    
    Color bgColor = (Color){0, 200, 100, 255};
    ClearBackground(bgColor);
    
    
    if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    else DrawRectangleRec(playButton, noColor);
    
    // Measure the width of the text
       
    int subtitleDeathWidth = MeasureText(subtitleDeath, subtitleDeathFontSize);
    int subtitleDeathPosX = (GetScreenWidth() - subtitleDeathWidth) / 2;
    
    int mainMenuBtnWidth = MeasureText(mainMenuBtn, mainMenuBtnFontSize);
    int mainMenuBtnPosX = (GetScreenWidth() - mainMenuBtnWidth) / 2;
    
    //DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, WHITE);
    DrawText(subtitleDeath, subtitleDeathPosX, GetScreenHeight()/2 - 100, subtitleDeathFontSize, WHITE);
    DrawText(mainMenuBtn, mainMenuBtnPosX, GetScreenHeight()/2 + 12, playBtnFontSize, WHITE);
    
   
    if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    resetScene();
    return 0;  
    }    
    
    return 2;
    
}

int winScene(){
    
    mousePoint = GetMousePosition();
    
    
    Color bgColor = (Color){0, 200, 100, 255};
    ClearBackground(bgColor);
    
    
    if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    else DrawRectangleRec(playButton, noColor);
    
    // Measure the width of the text
       
    int subtitleWinWidth = MeasureText(subtitleWin, subtitleWinFontSize);
    int subtitleWinPosX = (GetScreenWidth() - subtitleWinWidth) / 2;
    
    int mainMenuBtnWidth = MeasureText(mainMenuBtn, mainMenuBtnFontSize);
    int mainMenuBtnPosX = (GetScreenWidth() - mainMenuBtnWidth) / 2;
    
    //DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, WHITE);
    DrawText(subtitleWin, subtitleWinPosX, GetScreenHeight()/2 - 100, subtitleWinFontSize, WHITE);
    DrawText(mainMenuBtn, mainMenuBtnPosX, GetScreenHeight()/2 + 12, playBtnFontSize, WHITE);
    
   
    if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 0;  
    
    
    return 2;
    
}
