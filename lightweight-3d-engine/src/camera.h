#pragma once

class Camera {
public:
    Camera();

    float zoom;        // Zoom factor
    float offsetX;     // Camera offset X
    float offsetY;     // Camera offset Y

    float projectX(float x, float z) const;
    float projectY(float y, float z) const;
};
