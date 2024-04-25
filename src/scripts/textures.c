
Texture2D grassTexture;
Texture2D sandTexture;
Texture2D fieldTexture;
Texture2D wateredFieldTexture;
Texture2D seedFieldTexture;
Texture2D wateredSeedFieldTexture;
Texture2D emptyHand;
Texture2D drySprout;
Texture2D wateredSprout;
Texture2D smallWeedWateredSprout;
Texture2D bigWeedWateredSprout;
Texture2D plantedField;
Texture2D weedField;


Texture2D scaleTexture(Texture2D texture, int newWidth, int newHeight) {
    RenderTexture2D target = LoadRenderTexture(newWidth, newHeight);
    BeginTextureMode(target);

    // Draw the original texture onto the target texture, scaling it up
    DrawTexturePro(texture, (Rectangle){ 0, 0, texture.width, -texture.height }, 
                   (Rectangle){ 0, 0, newWidth, newHeight }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    EndTextureMode();
    return target.texture;
}

void loadTextures() {
    grassTexture = scaleTexture(LoadTexture("src/textures/1.png"), 64, 64);
    sandTexture = scaleTexture(LoadTexture("src/textures/2.png"), 64, 64);
    fieldTexture = scaleTexture(LoadTexture("src/textures/3.png"), 64, 64);
    wateredFieldTexture = scaleTexture(LoadTexture("src/textures/4.png"), 64, 64);
    seedFieldTexture = scaleTexture(LoadTexture("src/textures/5.png"), 64, 64);
    wateredSeedFieldTexture = scaleTexture(LoadTexture("src/textures/6.png"), 64, 64);
    emptyHand = scaleTexture(LoadTexture("src/textures/emptyHand.png"), 64, 64);
    drySprout = scaleTexture(LoadTexture("src/textures/5.png"), 64, 64);
    wateredSprout = scaleTexture(LoadTexture("src/textures/51.png"), 64, 64);
    smallWeedWateredSprout = scaleTexture(LoadTexture("src/textures/52.png"), 64, 64);
    bigWeedWateredSprout = scaleTexture(LoadTexture("src/textures/53.png"), 64, 64);
    plantedField = scaleTexture(LoadTexture("src/textures/311.png"), 64, 64);
    weedField = scaleTexture(LoadTexture("src/textures/32.png"), 64, 64);
}


void unloadTextures(){
    
    UnloadTexture(grassTexture);
    UnloadTexture(sandTexture);
    UnloadTexture(fieldTexture);
    UnloadTexture(wateredFieldTexture);
    UnloadTexture(seedFieldTexture);
    UnloadTexture(wateredSeedFieldTexture);
    UnloadTexture(emptyHand);
    UnloadTexture(drySprout);
    UnloadTexture(wateredSprout);
    UnloadTexture(smallWeedWateredSprout);
    UnloadTexture(bigWeedWateredSprout);
    UnloadTexture(plantedField);
    UnloadTexture(weedField);
 
}
