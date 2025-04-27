#include "world.h"

World::World(const Vector2D& gravity) : gravity_(gravity) {}

void World::addBody(const Body& body) {
    bodies_.push_back(body);
}

void World::step(double dt) {
    for (auto& body : bodies_) {
        body.applyForce(gravity_ * body.mass);
        body.update(dt);
    }

    // 🔥 Check for collisions after updating positions
    for (size_t i = 0; i < bodies_.size(); ++i) {
        for (size_t j = i + 1; j < bodies_.size(); ++j) {
            Vector2D delta = bodies_[i].position - bodies_[j].position;
            double distance = delta.magnitude();
            double minDist = bodies_[i].radius + bodies_[j].radius;

            if (distance <= minDist) {
                // Simple reaction: reverse velocities
                bodies_[i].velocity = bodies_[i].velocity * -1;
                bodies_[j].velocity = bodies_[j].velocity * -1;
            }
        }
    }
}

std::vector<Body>& World::getBodies()
{
    return bodies_;
}

