#include <SFML/Graphics.hpp>
#include "world.h"
#include <vector>
#include <cstdlib>
#include <ctime>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float TIME_STEP = 0.01f; // Smaller timestep = smoother simulation
const float GROUND_Y = 580.0f; // Ground height (slightly above bottom)

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Physics Engine!");

    World world(Vector2D(0.0, 98.0)); // Gravity downward (pixels/sec^2)

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create multiple bodies
    for (int i = 0; i < 10; ++i)
    {
        double mass = 1.0;
        double radius = 10.0 + std::rand() % 20; // Random radius between 10 and 30
        Vector2D position(100 + std::rand() % 600, 50 + std::rand() % 100);
        Body body(mass, radius, position);
        world.addBody(body);
    }

    sf::Clock clock;
    float accumulator = 0.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        accumulator += dt;

        while (accumulator >= TIME_STEP)
        {
            world.step(TIME_STEP);
        
            // Ground collision and bounce
            for (auto& body : world.getBodies()) // <-- NO CONST!
            {
                if (body.position.y + body.radius >= GROUND_Y)
                {
                    body.position.y = GROUND_Y - body.radius; // Push body above ground
                    body.velocity.y *= -0.7; // Bounce with damping
                }
            }
        
            accumulator -= TIME_STEP;
        }
        

        window.clear(sf::Color::Black);

        // Draw bodies
        for (const auto& body : world.getBodies())
        {
            sf::CircleShape circle(static_cast<float>(body.radius));
            circle.setOrigin(static_cast<float>(body.radius), static_cast<float>(body.radius));
            circle.setPosition(static_cast<float>(body.position.x), static_cast<float>(body.position.y));

            // Random color based on body
            circle.setFillColor(sf::Color(
                100 + (std::rand() % 155),
                100 + (std::rand() % 155),
                100 + (std::rand() % 155)
            ));

            window.draw(circle);
        }

        window.display();
    }

    return 0;
}
