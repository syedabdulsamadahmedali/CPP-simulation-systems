#include "camera.h"

Camera::Camera()
    : zoom(300.0f), offsetX(400.0f), offsetY(300.0f) // Center of screen
{}

float Camera::projectX(float x, float z) const {
    float scale = zoom / (z + zoom);
    return x * scale + offsetX;
}

float Camera::projectY(float y, float z) const {
    float scale = zoom / (z + zoom);
    return y * scale + offsetY;
}
