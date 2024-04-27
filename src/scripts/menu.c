


Vector2 mousePoint = {};
Color buttonColor = (Color){0, 0, 0, 50};
Color bgColor = (Color){0, 100, 100, 255};
Color noColor = (Color){0, 0, 0, 0};


Rectangle playButton = {832/2 - 100, 640/2, 200, 50};

const char *title = "FEED THE BEAST";
const int titleFontSize = 48;
const char *subtitle = "JACKIE EDITION";
const int subtitleFontSize = 40;
char *playBtn = "UwU";
const int playBtnFontSize = 30;


const char *subtitleDeath = "YOU DIE";
const int subtitleDeathFontSize = 40;
const char *mainMenuBtn = "Main Menu";
const int mainMenuBtnFontSize = 30;




const char *subtitleWinJackie = "You managed to feed Jackie:";
const int subtitleWinJackieFontSize = 35;


const int subtitleWinJackie1FontSize = 35;

const char *subtitleWinJackie2 = "coffee";
const int subtitleWinJackie2FontSize = 35;





int menuScene(){
    
    mousePoint = GetMousePosition();
    
    

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
    
    

    ClearBackground(bgColor);
    
    
    //if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    //else DrawRectangleRec(playButton, noColor);
    
    // Measure the width of the text
       
    int subtitleDeathWidth = MeasureText(subtitleDeath, subtitleDeathFontSize);
    int subtitleDeathPosX = (GetScreenWidth() - subtitleDeathWidth) / 2;
    
    int mainMenuBtnWidth = MeasureText(mainMenuBtn, mainMenuBtnFontSize);
    int mainMenuBtnPosX = (GetScreenWidth() - mainMenuBtnWidth) / 2;
    
    //DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, WHITE);
    DrawText(subtitleDeath, subtitleDeathPosX, GetScreenHeight()/2 - 100, subtitleDeathFontSize, WHITE);
    //DrawText(mainMenuBtn, mainMenuBtnPosX, GetScreenHeight()/2 + 12, playBtnFontSize, WHITE);
    
   
    //if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    //resetScene();
    //return 0;  
    //}    
    
    return 2;
    
}

int winScene(Player *player){
    
    mousePoint = GetMousePosition();
    
    
    
    ClearBackground(bgColor);
    
    
    //if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    //else DrawRectangleRec(playButton, noColor);
    
    // Measure the width of the text
       

    
    
    int subtitleWinJackieWidth = MeasureText(subtitleWinJackie, subtitleWinJackieFontSize);
    int subtitleWinJackiePosX = (GetScreenWidth() - subtitleWinJackieWidth) / 2;
    
    //printf("Player Points: %i\n", player->points);
    const char *pointsStr = TextFormat("%i", player->points);
    int subtitleWinJackie1Width = MeasureText(pointsStr, subtitleWinJackie1FontSize);
    int subtitleWinJackie1PosX = (GetScreenWidth() - subtitleWinJackie1Width) / 2;
    
    
    int subtitleWinJackie2Width = MeasureText(subtitleWinJackie2, subtitleWinJackie2FontSize);
    int subtitleWinJackie2PosX = (GetScreenWidth() - subtitleWinJackie2Width) / 2;
    
    
    
    

    
    //DrawText(title, titlePosX, GetScreenHeight()/2 - 150, titleFontSize, WHITE);
    //DrawText(subtitleWin, subtitleWinPosX, GetScreenHeight()/2 - 200, subtitleWinFontSize, WHITE);
    //DrawText(mainMenuBtn, mainMenuBtnPosX, GetScreenHeight()/2 + 12, playBtnFontSize, WHITE);
    //DrawText(player->points, subtitleWinPosX, GetScreenHeight()/2 - 100, subtitleWinFontSize, WHITE);
    DrawText(TextFormat(subtitleWinJackie), subtitleWinJackiePosX, 200, 35, WHITE);
    DrawText(TextFormat(pointsStr), subtitleWinJackie1PosX, 240, 35, WHITE);
    DrawText(TextFormat(subtitleWinJackie2), subtitleWinJackie2PosX, 280, 35, WHITE);
    //if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 0;  
    
    
    
    return 3;
    
}
