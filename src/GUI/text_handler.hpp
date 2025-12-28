#pragma once

#include <string>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"

using std::string;

namespace sf { class RenderWindow; }

class TextHandler {
    sf::Font font;
    const string& str;
    sf::Text text;
    sf::RenderWindow& window;

public:
    explicit TextHandler(const string& str, float object_x, float object_y, float object_width, float object_height, sf::RenderWindow& window, sf::Color color = sf::Color::Black, int font_size = 30, bool different_outline = false);

    void render_text() const;
};
