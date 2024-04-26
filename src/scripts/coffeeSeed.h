#ifndef COFFEE_SEED_H
#define COFFEE_SEED_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Texture2D texture;
    bool isActive;
    Rectangle collider;
    bool isEquipped;
} CoffeeSeed;

#endif
