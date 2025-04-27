#pragma once

#include <vector>
#include "object3d.h"
#include <SFML/Graphics.hpp>
#include "camera.h" 

class World {
    public:
        World();
    
        void generateDemoObjects();  // Create some cubes
        void update(float dt);
        void draw(sf::RenderWindow& window, const Camera& camera);

        private:
        std::vector<Object3D> objects_;
        float spawnTimer_ = 0.0f; // NEW: Time since last spawn    
    };
    
