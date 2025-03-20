#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <random>
#include <WordReader.h>

struct TextCircle {
    sf::CircleShape circle;
    sf::Text text;
    float speed;

    TextCircle(sf::Font& font, const std::string& word, sf::Vector2f pos, float spd)
        : text(font), speed(spd) {
        circle.setRadius(30);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(pos);

        text.setString(word);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(pos);
    }

    void move(float deltaTime) {
        sf::Vector2f movement(0.f, speed * deltaTime);
        circle.move(movement);
        text.move(movement);
    }

};

struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bullet(sf::Vector2f pos, sf::Vector2f dir) : velocity(dir * 300.f) {
        shape.setRadius(5);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(pos);
    }

    void move(float deltaTime) {
        shape.move(velocity * deltaTime);
    }
};

bool circlesIntersect(const sf::CircleShape& circle1, const sf::CircleShape& circle2) {
    float dx = circle1.getPosition().x - circle2.getPosition().x;
    float dy = circle1.getPosition().y - circle2.getPosition().y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = circle1.getRadius() + circle2.getRadius();
    return distanceSquared <= radiusSum * radiusSum;
}


int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Lab04 - Text Circles & Bullets");

    sf::Texture bgTexture("../../assets/space.jpg");
    sf::Texture handTexture("../../assets/hand.png");
    sf::Sprite background(bgTexture), hand(handTexture);

    sf::Font font("../../assets/Oswald/Oswald-Regular.ttf");

    std::vector<TextCircle> textCircles;
    std::vector<Bullet> bullets;
    sf::Clock spawnClock, deltaClock;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> speedDist(50, 100);
    WordReader reader("../../media/database1.txt");
    int score = 0;

    while (window.isOpen()) {
        std::optional event = window.pollEvent();
        while (event) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvt->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
            else if (const sf::Event::MouseButtonPressed* buttonEvt = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (buttonEvt->button == sf::Mouse::Button::Left) {
                    sf::Vector2f handPos(400, 550);
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    sf::Vector2f direction = mousePos - handPos;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    bullets.emplace_back(handPos, direction / length);
                }
            }
            event = window.pollEvent();
        }

        float deltaTime = deltaClock.restart().asSeconds();
        sf::Vector2f handPos(400, 550);
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePos - handPos;
        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
        hand.setPosition(handPos);
        hand.setRotation(sf::degrees(angle + 90.f));

        if (spawnClock.getElapsedTime().asSeconds() >= 1.0f) {
            spawnClock.restart();
            float xPos = static_cast<float>(rand() % 700 + 50);
            textCircles.emplace_back(font, reader.getRandomWord(), sf::Vector2f(xPos, 0), static_cast<float>(speedDist(gen)));
        }

        for (auto& tc : textCircles) tc.move(deltaTime);
        for (auto& b : bullets) b.move(deltaTime);

        textCircles.erase(remove_if(textCircles.begin(), textCircles.end(),
            [](const TextCircle& tc) { return tc.circle.getPosition().y > 600; }), textCircles.end());

        bullets.erase(remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return b.shape.getPosition().y < 0; }), bullets.end());

        for (auto b = bullets.begin(); b != bullets.end();) {
            bool bulletDestroyed = false;
            for (auto tc = textCircles.begin(); tc != textCircles.end();) {
                if (circlesIntersect(b->shape, tc->circle)) {
                    tc = textCircles.erase(tc);  // Remove the TextCircle
                    b = bullets.erase(b);        // Remove the Bullet
                    score += 10;                  // Update score
                    bulletDestroyed = true;       // Mark bullet as destroyed
                    break;
                }
                else {
                    ++tc;
                }
            }
            if (!bulletDestroyed) {
                ++b;  // Continue to next bullet if not destroyed
            }
        }


        window.clear();
        window.draw(background);
        for (auto& tc : textCircles) {
            window.draw(tc.circle);
            window.draw(tc.text);
        }
        for (auto& b : bullets) window.draw(b.shape);
        window.draw(hand);
        window.display();
    }
    return 0;
}
