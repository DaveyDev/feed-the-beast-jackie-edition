#include <raylib.h> // Include necessary Raylib headers

// Static variables to store the target position and camera offset
extern Vector2 target;
static Vector2 offset = { 0 };

// Function to initialize camera follow
void initCameraFollow(Vector2 playerPosition, Vector2 screenCenter) {
    target = playerPosition;
    offset = screenCenter;
}

// Function to update camera follow and return the calculated camera position
Vector2 updateCameraFollow() {
    // Calculate camera position based on the target and offset
    Vector2 position;
    position.x = target.x - offset.x;
    position.y = target.y - offset.y;
    return position;
}
    