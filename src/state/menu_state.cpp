#include <array>
#include <memory>
#include <filesystem>

#include "state.hpp"
#include "../GUI/button.hpp"
#include "menu_state.hpp"

#include "game_state.hpp"
#include "../config.hpp"
#include "../engine.hpp"

MenuState::MenuState(Engine* engine, sf::RenderWindow& window)
    : State(engine)
    , window{window}
    , title_text{
        "Chess",
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        window,
        {235, 235, 235},
        200,
        true
    }
    {

    buttons[0] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 3.0 / 6.0,
        SCREEN_WIDTH * 2.0 / 5.0 - 20,
        SCREEN_HEIGHT / 10.0,
        "White",
        window,
        [this]() {
            this->engine->audio_handler.play_click();
            this->white_selected = true;
        }
        , &white_selected
    );
    buttons[1] = std::make_unique<Button>(
        SCREEN_WIDTH / 2.0 + 20,
        SCREEN_HEIGHT * 3.0 / 6.0,
        SCREEN_WIDTH * 2.0 / 5.0 - 20,
        SCREEN_HEIGHT / 10.0,
        "Black",
        window,
        [this]() {
            this->engine->audio_handler.play_click();
            this->white_selected = false;
        }
        , &white_selected
        , true
    );
    buttons[2] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 4.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
    "Play",
        window,
        [this]() {
            this->engine->audio_handler.play_click();
            this->engine->change_state(new GameState(this->engine, this->window, this->white_selected));
        }
    );
    buttons[3] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 5.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        "Quit",
        window,
        [this]() {
            this->engine->audio_handler.play_click();
            this->engine->quit();
        }
    );
}

void MenuState::update() {
    position = sf::Mouse::getPosition(window);
}

void MenuState::render() {
    title_text.render_text();

    is_hovering = false;
    for (const auto& btn : buttons) {
        if (!btn) continue;

        Button& b = *btn;

        if (b.is_hovering(position)) {
            hovered_button = &b;
            is_hovering = true;
        }
        b.draw(); // <---- The reason all of this is even in render, is because of this cheeky call
    }
    if (!is_hovering) {
        hovered_button = nullptr;
    }
}

void MenuState::handle_events()  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!pressed) {
            if (hovered_button != nullptr) hovered_button->clicked();
            pressed = true;
        }
    } else {
        pressed = false;
    }
}