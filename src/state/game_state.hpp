#pragma once

#include "state.hpp"

namespace sf { class RenderWindow; }

class GameState : public State {

    sf::RenderWindow& window;

public:
    explicit GameState(Engine* engine, sf::RenderWindow& window);

    void draw_board() const;

    void update() override;
    void render() override;
    void handle_events() override;
};