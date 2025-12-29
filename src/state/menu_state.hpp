#pragma once


#include "state.hpp"
#include "../GUI/button.hpp"

class Engine;
namespace sf { class RenderWindow; }

class MenuState final : public State {
    sf::RenderWindow& window;

    std::array<std::unique_ptr<Button>, 4> buttons;

    TextHandler title_text;

    Button* hovered_button = nullptr;
    sf::Vector2i position;

    bool is_hovering = false;
    bool pressed = false;
    bool white_selected = true;
public:
    explicit MenuState(Engine* engine, sf::RenderWindow& window);

    void update() override;
    void render() override;
    void handle_events() override;
};
