cmake_minimum_required(VERSION 3.31)
project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Chess main.cpp
        src/engine.hpp
        src/state/state.hpp
        src/engine.cpp
        src/config.hpp
        src/state/menu_state.hpp
        src/state/menu_state.cpp
        src/GUI/text_handler.hpp
        src/GUI/text_handler.cpp
        src/GUI/button.hpp
        src/GUI/button.cpp
        src/state/game_state.hpp
        src/state/game_state.cpp
        src/GUI/audio_handler.hpp
        src/Chess/position.hpp
        src/Chess/position.cpp
        src/Chess/Utils/strings.hpp
        src/Chess/Utils/binary.hpp
)

target_compile_features(Chess PRIVATE cxx_std_20)
target_link_libraries(Chess PRIVATE SFML::Graphics SFML::Audio)