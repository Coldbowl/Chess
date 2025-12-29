#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_state.hpp"
#include "../config.hpp"

sf::Color white_square_color = { 236, 236, 208 };
sf::Color black_square_color = { 114, 149, 81 };


GameState::GameState(Engine *engine, sf::RenderWindow &window)
    : State(engine)
    , window{window}
{}

void GameState::draw_board() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square;
            square.setSize({ 100.f, 100.f });
            square.setPosition({ i * 100.f + (SCREEN_WIDTH - 800) / 2 , j * 100.f + 50.f });
            ((i + j) % 2 == 0) ? square.setFillColor(white_square_color) : square.setFillColor(black_square_color);
            window.draw(square);
        }
    }
}


void GameState::render() {
    draw_board();
}

void GameState::handle_events() {

}

void GameState::update() {

}



