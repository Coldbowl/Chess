#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "state/state.hpp"
#include "GUI/audio_handler.hpp"

class MenuState; // Forward declaration

inline constexpr double dt = 1.0 / 60.0;

class Engine {
    bool running = true;
    sf::Clock fpsClock;
    int frameCount = 0;
    float accumulator = 0.f;
    sf::RenderWindow window;
    sf::Clock frame_clock;

    State* current_state = nullptr;

    AudioHandler audio_handler;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    friend class MenuState;

public:
    Engine();

    ~Engine();

    void change_state(State* s);

    void run();

    void quit();

    void handle_events();

    void draw_background();
};
