#include "text_handler.hpp"

#include "SFML/System/Exception.hpp"

using std::string;

TextHandler::TextHandler(const string& str, const float object_x, const float object_y, const float object_width, const float object_height, sf::RenderWindow& window, const sf::Color color, const int font_size, const bool different_outline)
: str{std::move(str)}
, text{font, str}
, window{window}
{
    if (!font.openFromFile("src/Assets/Fonts/Fontspring-DEMO-7_rustica-bold.otf")) {
        throw sf::Exception("Unable to open provided path to font");
    }
    text.setCharacterSize(font_size);
    if (different_outline) {
        text.setOutlineColor({20, 20, 20});
        text.setOutlineThickness(4.f);
    }

    const sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    text.setPosition({
        object_x + object_width  / 2.f,
        object_y + object_height / 2.f
    });

    text.setFillColor(color);
}

void TextHandler::render_text() const {
    window.draw(text);
}
