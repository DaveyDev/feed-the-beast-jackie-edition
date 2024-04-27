#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"



typedef struct {
    Texture2D texture;       // Texture containing the animation frames
    Rectangle* frames;       // Array of rectangles defining each frame in the texture
    int frameCount;          // Number of frames in the animation
    int currentFrame;        // Index of the current frame being displayed
    float frameTime;         // Time duration for each frame (in seconds)
    float currentTime;       // Time elapsed since the last frame change
} Animation;


void UpdateAnimation(Animation *anim, float deltaTime);

#endif // ANIMATION_H