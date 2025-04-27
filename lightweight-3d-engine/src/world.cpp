#include "world.h"

World::World() {}

void World::generateDemoObjects() {
    // Generate some random 3D objects
    objects_.emplace_back(-50.f, -100.f, 100.f, 20.f, sf::Color::Red);
    objects_.emplace_back(50.f, -80.f, 200.f, 20.f, sf::Color::Green);
    objects_.emplace_back(-100.f, -120.f, 150.f, 20.f, sf::Color::Blue);
    objects_.emplace_back(0.f, -90.f, 250.f, 20.f, sf::Color::Yellow);
    objects_.emplace_back(80.f, -110.f, 180.f, 20.f, sf::Color::Magenta);
}

void World::update(float dt) {
    // Update all objects
    for (auto& obj : objects_) {
        obj.update(dt);
    }

    // Update spawn timer
    spawnTimer_ += dt;

    // Spawn new object every 2 seconds
    if (spawnTimer_ >= 2.0f) {
        float x = static_cast<float>(rand() % 800 - 400); // random X between -400 and 400
        float y = -100.0f; // Start from high up
        float z = static_cast<float>(rand() % 500 + 50);  // random Z between 50 and 550
        float radius = static_cast<float>((rand() % 10) + 10); // random radius 10-20
        sf::Color color(rand() % 256, rand() % 256, rand() % 256); // random color

        objects_.emplace_back(x, y, z, radius, color);

        spawnTimer_ = 0.0f; // reset timer
    }
}


void World::draw(sf::RenderWindow& window, const Camera& camera) {
    // === Draw ground first ===
    sf::RectangleShape ground(sf::Vector2f(1600, 50)); // width, height
    ground.setOrigin(800, 25); // center it
    ground.setPosition(camera.projectX(0, 0), camera.projectY(300, 0)); // project ground Y at 300
    ground.setFillColor(sf::Color(50, 150, 50)); // dark green ground
    window.draw(ground);

    // === Draw objects ===
    for (const auto& obj : objects_) {
        obj.draw(window, camera);
    }
}

