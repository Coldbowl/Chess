#include <cassert>

#include "engine.hpp"
#include "state/menu_state.hpp"
#include "config.hpp"
#include "GUI/audio_handler.hpp"

sf::SoundBuffer AudioHandler::sound_buffer;

const std::string CLICK_PATH = "../Chess/src/Assets/SFX/click_sound.wav";
const std::string BACKGROUND_PATH = "src/Assets/Images/Backgrounds/blurred_background.png";

Engine::Engine()
    : window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Chess")
    , audio_handler(CLICK_PATH)
    , background_sprite(background_texture) {
    if (!background_texture.loadFromFile(BACKGROUND_PATH)) {
        throw std::runtime_error("Failed to load background texture");
    }

    background_sprite.setTexture(background_texture, true);
}

Engine::~Engine() {
    delete current_state;
}

void Engine::change_state(State* s) {
    assert(s != nullptr);
    if (current_state == s) return;
    delete current_state;
    current_state = s;
}

void Engine::run() {
    change_state(new MenuState(this, window));
    while (running) {
        handle_events();
        current_state->handle_events();
        current_state->update();
        window.clear();
        draw_background();
        current_state->render();
        window.display();
    }
    delete current_state;
    window.close();
}

void Engine::quit() {
    running = false;
}

void Engine::handle_events() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            quit();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                quit();
            }
        }
    }
}

void Engine::draw_background() {
    window.draw(background_sprite);
}
