#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Robot.h"
#include <iostream>

const int CELL_SIZE = 50;
const char* FONT_PATH = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";

void drawMap(sf::RenderWindow& window, const Map& map, const Robot& robot) {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.setFillColor(sf::Color::Black);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::White);
            window.draw(cell);

            if (grid[y][x] == 1) {
                sf::RectangleShape object(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                object.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                object.setFillColor(sf::Color::White);
                object.setOutlineThickness(1);
                object.setOutlineColor(sf::Color::White);
                window.draw(object);
            }
        }
    }

    // Draw the robot as a circle
    sf::CircleShape robotShape(CELL_SIZE / 2);
    robotShape.setPosition(robot.getX() * CELL_SIZE, robot.getY() * CELL_SIZE);
    robotShape.setFillColor(sf::Color::Red);
    robotShape.setOutlineThickness(1);
    robotShape.setOutlineColor(sf::Color::White);
    window.draw(robotShape);
}

void drawButtons(sf::RenderWindow& window, const sf::Font& font) {
    // Up button
    sf::RectangleShape upButton(sf::Vector2f(100, 50));
    upButton.setPosition(550, 50);
    upButton.setFillColor(sf::Color::White);
    upButton.setOutlineThickness(1);
    upButton.setOutlineColor(sf::Color::Black);
    window.draw(upButton);

    sf::Text upText("UP", font, 20);
    upText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = upText.getLocalBounds();
    upText.setOrigin(textRect.left + textRect.width/2.0f,
                     textRect.top + textRect.height/2.0f);
    upText.setPosition(upButton.getPosition().x + upButton.getSize().x/2.0f,
                      upButton.getPosition().y + upButton.getSize().y/2.0f);
    window.draw(upText);

    // Down button
    sf::RectangleShape downButton(sf::Vector2f(100, 50));
    downButton.setPosition(550, 150);
    downButton.setFillColor(sf::Color::White);
    downButton.setOutlineThickness(1);
    downButton.setOutlineColor(sf::Color::Black);
    window.draw(downButton);

    sf::Text downText("DOWN", font, 20);
    downText.setFillColor(sf::Color::Black);
    textRect = downText.getLocalBounds();
    downText.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    downText.setPosition(downButton.getPosition().x + downButton.getSize().x/2.0f,
                        downButton.getPosition().y + downButton.getSize().y/2.0f);
    window.draw(downText);

    // Left button
    sf::RectangleShape leftButton(sf::Vector2f(100, 50));
    leftButton.setPosition(450, 100);
    leftButton.setFillColor(sf::Color::White);
    leftButton.setOutlineThickness(1);
    leftButton.setOutlineColor(sf::Color::Black);
    window.draw(leftButton);

    sf::Text leftText("LEFT", font, 20);
    leftText.setFillColor(sf::Color::Black);
    textRect = leftText.getLocalBounds();
    leftText.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    leftText.setPosition(leftButton.getPosition().x + leftButton.getSize().x/2.0f,
                        leftButton.getPosition().y + leftButton.getSize().y/2.0f);
    window.draw(leftText);

    // Right button
    sf::RectangleShape rightButton(sf::Vector2f(100, 50));
    rightButton.setPosition(650, 100);
    rightButton.setFillColor(sf::Color::White);
    rightButton.setOutlineThickness(1);
    rightButton.setOutlineColor(sf::Color::Black);
    window.draw(rightButton);

    sf::Text rightText("RIGHT", font, 20);
    rightText.setFillColor(sf::Color::Black);
    textRect = rightText.getLocalBounds();
    rightText.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);
    rightText.setPosition(rightButton.getPosition().x + rightButton.getSize().x/2.0f,
                         rightButton.getPosition().y + rightButton.getSize().y/2.0f);
    window.draw(rightText);

    // Sensor button
    sf::RectangleShape sensorButton(sf::Vector2f(100, 50));
    sensorButton.setPosition(550, 250);
    sensorButton.setFillColor(sf::Color::White);
    sensorButton.setOutlineThickness(1);
    sensorButton.setOutlineColor(sf::Color::Black);
    window.draw(sensorButton);

    sf::Text sensorText("SENSOR", font, 20);
    sensorText.setFillColor(sf::Color::Black);
    textRect = sensorText.getLocalBounds();
    sensorText.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top + textRect.height/2.0f);
    sensorText.setPosition(sensorButton.getPosition().x + sensorButton.getSize().x/2.0f,
                          sensorButton.getPosition().y + sensorButton.getSize().y/2.0f);
    window.draw(sensorText);
}

bool isButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int main() {
    Map map(10, 10);
    map.addObject(2, 3, 3, 2);
    map.addObject(5, 5, 2, 3);
    Robot robot(1, 1, map, 0.1);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot Localization");
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Error loading font from " << FONT_PATH << std::endl;
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::RectangleShape upButton(sf::Vector2f(100, 50));
                upButton.setPosition(550, 50);
                sf::RectangleShape downButton(sf::Vector2f(100, 50));
                downButton.setPosition(550, 150);
                sf::RectangleShape leftButton(sf::Vector2f(100, 50));
                leftButton.setPosition(450, 100);
                sf::RectangleShape rightButton(sf::Vector2f(100, 50));
                rightButton.setPosition(650, 100);
                sf::RectangleShape sensorButton(sf::Vector2f(100, 50));
                sensorButton.setPosition(550, 250);

                if (isButtonClicked(upButton, mousePos)) {
                    robot.moveUp();
                } else if (isButtonClicked(downButton, mousePos)) {
                    robot.moveDown();
                } else if (isButtonClicked(leftButton, mousePos)) {
                    robot.moveLeft();
                } else if (isButtonClicked(rightButton, mousePos)) {
                    robot.moveRight();
                } else if (isButtonClicked(sensorButton, mousePos)) {
                    std::vector<int> readings = robot.getSensorReading();
                    std::cout << "Sensor readings: ";
                    for (int reading : readings) {
                        std::cout << reading << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);
        drawMap(window, map, robot);
        drawButtons(window, font);
        window.display();
    }

    return 0;
}