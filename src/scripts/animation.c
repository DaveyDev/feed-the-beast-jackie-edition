#include "animation.h"

void updateAnimation(Animation *anim, float deltaTime) {
    anim->currentTime += deltaTime;
    if (anim->currentTime >= anim->frameTime) {
        anim->currentTime = 0.0f;
        anim->currentFrame = (anim->currentFrame + 1) % anim->frameCount;
    }
}

// Other animation functions...
