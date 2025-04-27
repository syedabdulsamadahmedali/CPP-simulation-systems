#pragma once
#include "vector2d.h"

class Body {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    double mass;
    double radius; // 🔥 NEW

    Body(double m, double r, const Vector2D& pos);

    void applyForce(const Vector2D& force);
    void update(double dt);
};
