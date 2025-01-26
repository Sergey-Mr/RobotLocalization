#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Robot.h"
#include <iostream>
#include <sstream>

const int CELL_SIZE = 50;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const char* FONT_PATH = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";

// Add hover effect for buttons
sf::RectangleShape createButton(float x, float y, const sf::Vector2f& size, bool isHovered) {
    sf::RectangleShape button(size);
    button.setPosition(x, y);
    if (isHovered) {
        button.setFillColor(sf::Color(220, 220, 220));
    } else {
        button.setFillColor(sf::Color::White);
    }
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color(100, 100, 100));
    return button;
}

void drawMap(sf::RenderWindow& window, const Map& map, const Robot& robot) {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x * CELL_SIZE + 50, y * CELL_SIZE + 50);
            cell.setFillColor(sf::Color(20, 20, 20));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(cell);

            if (grid[y][x] == 1) {
                sf::RectangleShape object(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                object.setPosition(x * CELL_SIZE + 50, y * CELL_SIZE + 50);
                object.setFillColor(sf::Color::White);
                object.setOutlineThickness(2);
                object.setOutlineColor(sf::Color(200, 200, 200));
                window.draw(object);
            }
        }
    }

    sf::CircleShape robotShape(CELL_SIZE / 2);
    robotShape.setPosition(robot.getX() * CELL_SIZE + 50, robot.getY() * CELL_SIZE + 50);
    robotShape.setFillColor(sf::Color(255, 50, 50));
    robotShape.setOutlineThickness(2);
    robotShape.setOutlineColor(sf::Color(200, 0, 0));
    window.draw(robotShape);
}

void drawUI(sf::RenderWindow& window, const sf::Font& font, const std::vector<int>& sensorReadings, const sf::Vector2i& mousePos) {
    sf::Text title("Robot Localization Simulator", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 10);
    window.draw(title);

    // Calculate center position for the joystick layout
    float centerX = WINDOW_WIDTH - 300;
    float centerY = 250;
    float buttonWidth = 100;
    float buttonHeight = 50;
    float spacing = 60;

    std::vector<std::pair<sf::RectangleShape, std::string>> buttons = {
        {createButton(centerX, centerY - spacing, sf::Vector2f(buttonWidth, buttonHeight), false), "UP"},
        {createButton(centerX, centerY + spacing, sf::Vector2f(buttonWidth, buttonHeight), false), "DOWN"},
        {createButton(centerX - spacing, centerY, sf::Vector2f(buttonWidth, buttonHeight), false), "LEFT"},
        {createButton(centerX + spacing, centerY, sf::Vector2f(buttonWidth, buttonHeight), false), "RIGHT"},
        {createButton(centerX, centerY + spacing * 2.5, sf::Vector2f(buttonWidth, buttonHeight), false), "SENSOR"}
    };

    for (const auto& button : buttons) {
        window.draw(button.first);
        sf::Text text(button.second, font, 20);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        text.setPosition(button.first.getPosition().x + button.first.getSize().x/2.0f,
                        button.first.getPosition().y + button.first.getSize().y/2.0f);
        window.draw(text);
    }

    if (!sensorReadings.empty()) {
        sf::RectangleShape sensorPanel(sf::Vector2f(300, 100));
        sensorPanel.setPosition(WINDOW_WIDTH - 350, WINDOW_HEIGHT - 150);
        sensorPanel.setFillColor(sf::Color(40, 40, 40));
        sensorPanel.setOutlineThickness(2);
        sensorPanel.setOutlineColor(sf::Color(100, 100, 100));
        window.draw(sensorPanel);

        std::stringstream ss;
        ss << "Sensor Readings:\n";
        for (int reading : sensorReadings) {
            ss << reading << " ";
        }
        sf::Text sensorText(ss.str(), font, 16);
        sensorText.setFillColor(sf::Color::White);
        sensorText.setPosition(WINDOW_WIDTH - 340, WINDOW_HEIGHT - 140);
        window.draw(sensorText);
    }
}

bool isButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int main() {
    Map map(10, 10);
    map.addObject(2, 3, 3, 2);
    map.addObject(5, 5, 2, 3);
    Robot robot(1, 1, map, 0.1);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Robot Localization");
    window.setFramerateLimit(60);
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Error loading font from " << FONT_PATH << std::endl;
        return -1;
    }

    std::vector<int> currentSensorReadings;

    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                std::vector<sf::RectangleShape> buttons;
                float centerX = WINDOW_WIDTH - 300;
                float centerY = 250;
                float buttonWidth = 100;
                float buttonHeight = 50;
                float spacing = 60;

                buttons.push_back(createButton(centerX, centerY - spacing, sf::Vector2f(buttonWidth, buttonHeight), false));
                buttons.push_back(createButton(centerX, centerY + spacing, sf::Vector2f(buttonWidth, buttonHeight), false));
                buttons.push_back(createButton(centerX - spacing, centerY, sf::Vector2f(buttonWidth, buttonHeight), false));
                buttons.push_back(createButton(centerX + spacing, centerY, sf::Vector2f(buttonWidth, buttonHeight), false));
                buttons.push_back(createButton(centerX, centerY + spacing * 2.5, sf::Vector2f(buttonWidth, buttonHeight), false));
                if (isButtonClicked(buttons[0], mousePos)) {
                    robot.moveUp();
                } else if (isButtonClicked(buttons[1], mousePos)) {
                    robot.moveDown();
                } else if (isButtonClicked(buttons[2], mousePos)) {
                    robot.moveLeft();
                } else if (isButtonClicked(buttons[3], mousePos)) {
                    robot.moveRight();
                } else if (isButtonClicked(buttons[4], mousePos)) {
                    currentSensorReadings = robot.getSensorReading();
                }
            }
        }

        window.clear(sf::Color(10, 10, 10));
        drawMap(window, map, robot);
        drawUI(window, font, currentSensorReadings, mousePos);
        window.display();
    }

    return 0;
}