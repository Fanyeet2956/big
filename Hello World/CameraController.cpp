//CameraController.cpp
#include "CameraController.h"
#include "Globals.h"

Camera2D CreateCamera(Vector2 target, float zoom) {
    Camera2D cam = {};
    cam.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    cam.target = target;
    cam.rotation = 0.0f;
    cam.zoom = zoom;
    return cam;
}

