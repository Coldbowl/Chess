#include "button.hpp"

#include <string>
#include <utility>

#include "text_handler.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using std::string;

Button::Button(const float button_x, const float button_y, const float button_width, const float button_height, string text, sf::RenderWindow& window, std::function<void()> on_click, const bool* selected, const bool inverted, const sf::Color color)
    : button_x{button_x}
      , button_y{button_y}
      , button_width{button_width}
      , button_height{button_height}
      , text{std::move(text)}
      , window{window}
      , color{color}
      , selected{selected}
      , inverted{inverted}
      , text_handler(this->text, button_x, button_y, button_width, button_height, window)
      , on_click{std::move(on_click)}
      {

    button.setPosition({button_x, button_y});
    button.setSize({button_width, button_height});

    if (selected != nullptr) changeable = true;

    if (changeable && *selected == true) {
        button.setFillColor(hover_color);
    } else {
        button.setFillColor(color);
    }
}

void Button::draw() {
    if (changeable) {
        if (*selected && !inverted) {
            button.setFillColor(hover_color);
        } else if (*selected && inverted) {
            button.setFillColor(color);
        } else if (*selected == false && inverted) {
            button.setFillColor(hover_color);
        } else {
            button.setFillColor(color);
        }
    }
    window.draw(button);
    text_handler.render_text();
}

bool Button::is_hovering(const sf::Vector2i& mouse_position) {
    if (!(mouse_position.x > button_x && mouse_position.x < button_x + button_width && mouse_position.y > button_y  && mouse_position.y < button_y + button_height)) {
        button.setFillColor(color);
        return false;
    }
    button.setFillColor(hover_color);
    return true;
}

void Button::clicked() const {
    if (on_click) {
        on_click();
    }
}
