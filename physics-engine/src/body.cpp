#include "body.h"

Body::Body(double m, double r, const Vector2D& pos) 
    : mass(m), radius(r), position(pos), velocity(0, 0), acceleration(0, 0) {}


void Body::applyForce(const Vector2D& force) {
    Vector2D f = force / mass; // F = ma -> a = F/m
    acceleration = acceleration + f;
}

void Body::update(double dt) {
    velocity = velocity + (acceleration * dt);
    position = position + (velocity * dt);
    acceleration = Vector2D(0, 0); // Reset acceleration each frame
}
