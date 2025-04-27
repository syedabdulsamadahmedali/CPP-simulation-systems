#include <SFML/Graphics.hpp>
#include "camera.h"
#include "world.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lightweight 3D Engine");

    Camera camera;
    World world;

    world.generateDemoObjects(); // Create some cubes

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds(); // Make sure dt is here!

        const float moveSpeed = 200.0f; 
        const float zoomSpeed = 100.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.offsetY -= moveSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.offsetY += moveSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera.offsetX -= moveSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera.offsetX += moveSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            camera.zoom += zoomSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            camera.zoom -= zoomSpeed * dt;

        world.update(dt);

        window.clear(sf::Color::Black);
        world.draw(window, camera);
        window.display();
    }

    return 0;
}
