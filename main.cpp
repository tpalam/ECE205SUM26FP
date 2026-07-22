#include <SFML/Graphics.hpp>

int main() {
    // Create a window that is 1000 pixels wide and 600 pixels tall.
    sf::RenderWindow window(
        sf::VideoMode(1000, 600),
        "Moving Box"
    );

    // Limit the game to 60 frames per second.
    window.setFramerateLimit(60);

    // Create a square.
    sf::RectangleShape box;

    // Give the square a width and height of 50 pixels.
    box.setSize(sf::Vector2f(50.f, 50.f));

    // Place the square near the left side of the window.
    box.setPosition(50.f, 275.f);

    // Give the square a color.
    box.setFillColor(sf::Color::Cyan);

    // This clock measures the time between frames.
    sf::Clock clock;

    // Keep running while the window is open.
    while (window.isOpen()) {
        // Measure how many seconds passed since the previous frame.
        float deltaTime = clock.restart().asSeconds();

        // Check all window events.
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close the window when the user clicks the close button.
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Speed is measured in pixels per second.
        float speed = 200.f;

        // Move the box to the right.
        box.move(speed * deltaTime, 0.f);

        // Clear the previous frame.
        window.clear(sf::Color(25, 25, 40));

        // Draw the box.
        window.draw(box);

        // Show the completed frame.
        window.display();
    }

    return 0;
}