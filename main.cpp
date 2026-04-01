#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <optional>
#include <cmath>

#define g 9.81f

int main() {
    sf::Clock dtclock;
    sf::Font font;
    if (!font.openFromFile("../assets/fonts/arialceb.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    const sf::Vector2u windowSize(1280, 960);
    const sf::Vector2f surfaceSize(1280.f, 300.f);
    const sf::Vector2f bodySize(100.f, 100.f);

    float mass = 5.0f;
    float coefficient = 2.0f;
    float pushing_force = 0.0f;
    float damping_force = 0.5f;

    sf::Vector2f velocity({0.0f, 0.0f});
    sf::Vector2f position({0.0f, 0.0f});

    sf::RenderWindow window(sf::VideoMode(windowSize), "My sim");
    window.setFramerateLimit(60);

    sf::RectangleShape surface(surfaceSize);
    surface.setFillColor(sf::Color::Blue);

    surface.setPosition({0.f, static_cast<float>(windowSize.y) - surfaceSize.y});

    sf::RectangleShape body(bodySize);
    body.setFillColor(sf::Color::White);
    body.setPosition({600.f, surface.getPosition().y - bodySize.y});
    position = body.getPosition();

    sf::Text force_counter(font, "Force: 0", 24);
    force_counter.setFillColor(sf::Color::White);
    force_counter.setPosition({10.f, 10.f});

    sf::Text body_velocity(font, "Velocity: 0", 24);
    body_velocity.setFillColor(sf::Color::White);
    body_velocity.setPosition({10.f, 40.f});

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            pushing_force += 10.f;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            pushing_force -= 10.f;
        }

        force_counter.setString("Force Applied: " + std::to_string((int)pushing_force));
        body_velocity.setString("Velocity of the body: " + std::to_string((int)velocity.x));

        float friction = 0.0f;
        if (velocity.x > 0) friction = -coefficient * g * mass;
        else if (velocity.x < 0) friction = coefficient * g * mass;

        float acceleration = coefficient * g;

        float dt = dtclock.restart().asSeconds();

        velocity.x += dt * acceleration;
        position.x += dt * velocity.x;

        if (position.x >= window.getSize().x - body.getSize().x) {
            position.x = window.getSize().x - body.getSize().x;
            velocity.x = -velocity.x * damping_force;
            pushing_force = 0;
        }
        if (position.x <= 0) {
            position.x = 0;
            velocity.x = -velocity.x * damping_force;
            pushing_force = 0;
        }

        if (std::abs(velocity.x) < 1.0f && pushing_force == 0) {
            velocity.x = 0;
        }

        window.clear();
        window.draw(surface);

        body.setPosition(position);
        window.draw(body);

        window.draw(force_counter);
        window.draw(body_velocity);
        window.display();
    }
    return 0;
}