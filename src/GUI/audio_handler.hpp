#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Exception.hpp>

class AudioHandler {
    static sf::SoundBuffer sound_buffer;
    sf::Sound click_sound;

public:
    AudioHandler(const std::string& sound_path)
        : click_sound{sound_buffer}
    {
        if (sound_buffer.getSampleCount() == 0) {
            if (!sound_buffer.loadFromFile(sound_path)) {
                throw sf::Exception("Unable to load file from provided path");
            }
        }
        click_sound.setBuffer(sound_buffer);
    }

    void play_click() {
        click_sound.play();
    }
};