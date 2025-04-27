#pragma once
#include "body.h"
#include <vector>

class World {
public:
    World(const Vector2D& gravity);

    void addBody(const Body& body);
    void step(double dt);

    const std::vector<Body>& getBodies() const; // 🔥 NEW Getter for bodies
    std::vector<Body>& getBodies();


private:
    Vector2D gravity_;
    std::vector<Body> bodies_;
};
