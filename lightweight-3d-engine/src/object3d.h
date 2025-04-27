#pragma once
#include <SFML/Graphics.hpp>
#include "camera.h"

class Object3D {
public:
    Object3D(float x, float y, float z, float radius, sf::Color color);

    void draw(sf::RenderWindow& window, const Camera& camera) const;
    void update(float dt); // Gravity / motion

    private:
    float x_, y_, z_;
    float radius_;
    sf::Color color_;

    // NEW
    float velocityX_ = 0.0f;
    float velocityY_ = 0.0f;
  // Color
};
