#pragma once

#include <string>
#include <functional>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "text_handler.hpp"


// Forward declaration
namespace sf { class RenderWindow; }

using std::string;

class Button {
    float button_x;
    float button_y;
    float button_width;
    float button_height;
    string text;
    sf::RenderWindow& window;
    sf::Color color;
    sf::Color hover_color = sf::Color{128,128,128};
    const bool* selected;
    bool changeable = false;
    bool inverted;

    TextHandler text_handler;

    sf::RectangleShape button;
    std::function<void()> on_click;

    static sf::SoundBuffer buffer;
    sf::Sound sound;



public:
    explicit Button(float button_x, float button_y, float button_width, float button_height, string text, sf::RenderWindow& window, std::function<void()> on_click, const bool* selected = nullptr, bool inverted = false, sf::Color color = sf::Color::White);

    void draw();

    bool is_hovering(const sf::Vector2i& mouse_position);

    void clicked();
};