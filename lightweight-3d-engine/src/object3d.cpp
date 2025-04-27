#include "object3d.h"

Object3D::Object3D(float x, float y, float z, float radius, sf::Color color)
    : x_(x), y_(y), z_(z), radius_(radius), color_(color)
    
{
    // Give small random velocities
velocityX_ = static_cast<float>((rand() % 200) - 100); // random -100 to +100
velocityY_ = 0.0f;

}

void Object3D::update(float dt) {
    static float gravity = 300.0f;
    static float bounceDamping = 0.7f;

    // Apply gravity
    velocityY_ += gravity * dt;

    // Apply velocity
    x_ += velocityX_ * dt;
    y_ += velocityY_ * dt;

    const float groundY = 300.0f;
    if (y_ > groundY) {
        y_ = groundY;
        velocityY_ = -velocityY_ * bounceDamping; // Invert Y with damping
    }
}



void Object3D::draw(sf::RenderWindow& window, const Camera& camera) const {
    float screenX = camera.projectX(x_, z_);
    float screenY = camera.projectY(y_, z_);

    float scale = camera.zoom / (z_ + camera.zoom);
    float scaledRadius = radius_ * scale;

    sf::CircleShape circle(scaledRadius);
    circle.setOrigin(scaledRadius, scaledRadius); // Center origin
    circle.setPosition(screenX, screenY);
    circle.setFillColor(color_);

    window.draw(circle);
}
