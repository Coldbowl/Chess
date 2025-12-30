#include "game_state.hpp"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../config.hpp"
#include "../Chess/Position.hpp"
constexpr sf::Color white_square_color = { 236, 236, 208 };
constexpr sf::Color black_square_color = { 114, 149, 81 };

constexpr int TILE_SIZE = 160;
constexpr float SCALE = 100.f / 160.f;
const std::string PIECES_PATH = "src/Assets/Images/Chess Pieces/Chess Pieces Sprite.png";

GameState::GameState(Engine *engine, sf::RenderWindow &window, const bool is_player_white)
    : State(engine)
    , is_player_white(is_player_white)
    , window(window)
    , white_pawn_sprite(pieces_texture)
    , white_rook_sprite(pieces_texture)
    , white_knight_sprite(pieces_texture)
    , white_bishop_sprite(pieces_texture)
    , white_queen_sprite(pieces_texture)
    , white_king_sprite(pieces_texture)
    , black_pawn_sprite(pieces_texture)
    , black_rook_sprite(pieces_texture)
    , black_knight_sprite(pieces_texture)
    , black_bishop_sprite(pieces_texture)
    , black_queen_sprite(pieces_texture)
    , black_king_sprite(pieces_texture)
{
    if (!pieces_texture.loadFromFile(PIECES_PATH)) {
        throw std::runtime_error("Failed to load piece sprite from provided path");
    }

    white_king_sprite.setTextureRect({ {0 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_king_sprite.setScale({ SCALE, SCALE });

    white_queen_sprite.setTextureRect({ {1 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_queen_sprite.setScale({ SCALE, SCALE });

    white_bishop_sprite.setTextureRect({ {2 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_bishop_sprite.setScale({ SCALE, SCALE });

    white_knight_sprite.setTextureRect({ {3 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_knight_sprite.setScale({ SCALE, SCALE });

    white_rook_sprite.setTextureRect({ {4 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_rook_sprite.setScale({ SCALE, SCALE });

    white_pawn_sprite.setTextureRect({ {5 * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE} });
    white_pawn_sprite.setScale({ SCALE, SCALE });

    black_king_sprite.setTextureRect({ {0 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_king_sprite.setScale({ SCALE, SCALE });

    black_queen_sprite.setTextureRect({ {1 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_queen_sprite.setScale({ SCALE, SCALE });

    black_bishop_sprite.setTextureRect({ {2 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_bishop_sprite.setScale({ SCALE, SCALE });

    black_knight_sprite.setTextureRect({ {3 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_knight_sprite.setScale({ SCALE, SCALE });

    black_rook_sprite.setTextureRect({ {4 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_rook_sprite.setScale({ SCALE, SCALE });

    black_pawn_sprite.setTextureRect({ {5 * TILE_SIZE, 1 * TILE_SIZE}, {TILE_SIZE, TILE_SIZE} });
    black_pawn_sprite.setScale({ SCALE, SCALE });

    current_position = Position::from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    current_position.update_piece_bitboards();
}

void GameState::draw_board() const {
    sf::RectangleShape back_shape;
    back_shape.setSize({ 900.f, 900.f });
    back_shape.setPosition({ (SCREEN_WIDTH - 900) / 2 , 0 });
    back_shape.setFillColor({41, 41, 41});
    window.draw(back_shape);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square;
            square.setSize({ 100.f, 100.f });
            square.setPosition({ i * 100.f + (SCREEN_WIDTH - 800) / 2, j * 100.f + 50.f });
            ((i + j) % 2 == 0) ? square.setFillColor(white_square_color) : square.setFillColor(black_square_color);
            window.draw(square);
        }
    }
}

void GameState::draw_pieces() const {
    struct PieceInfo {
        sf::Sprite* sprite;
        uint64_t (Position::*getter)() const;
        bool single;
    };

    // Draw white pieces
    for (int p = 0; p < 6; p++) {
        sf::Sprite* sprite = white_bitboards[p].sprite;
        const uint64_t bb = (current_position.*(white_bitboards[p].getter))();
        for (int i = 63; i >= 0; --i) {
            if (bb & (1ULL << i)) {
                int drawing_i;
                (is_player_white) ? drawing_i = 63 - i : drawing_i = i;
                sprite->setPosition({
                    (drawing_i % 8) * 100.f + (SCREEN_WIDTH - 800) / 2,
                    (drawing_i / 8) * 100.f + 50.f
                });
                window.draw(*sprite);
                if (white_bitboards[p].single) break;
            }
        }
    }

    // Draw black pieces
    for (int p = 0; p < 6; p++) {
        sf::Sprite* sprite = black_bitboards[p].sprite;
        uint64_t bb = (current_position.*(black_bitboards[p].getter))();
        for (int i = 63; i >= 0; --i) {
            if (bb & (1ULL << i)) {
                int drawing_i;
                (is_player_white) ? drawing_i = 63 - i : drawing_i = i;
                sprite->setPosition({
                    (drawing_i % 8) * 100.f + (SCREEN_WIDTH - 800) / 2,
                    (drawing_i / 8) * 100.f + 50.f
                });
                window.draw(*sprite);
                if (black_bitboards[p].single) break;
            }
        }
    }
}

void GameState::clicked_square() {
    mouse_position = sf::Mouse::getPosition(window);
    constexpr int left_x = (SCREEN_WIDTH - 800) / 2;
    constexpr int right_x = 800 + left_x;

    constexpr int top_y = 50;
    constexpr int bottom_y = 800 + top_y;

    std::cout << move.from << "\n";

    if (mouse_position.x > left_x && mouse_position.x < right_x && mouse_position.y > top_y && mouse_position.y < bottom_y) {
        if (const uint64_t square_clicked = (mouse_position.x - left_x) / 100 + (mouse_position.y - top_y) / 100 * 8; 1ULL << square_clicked & (current_position.get_black_piece_bitboard() | current_position.get_white_piece_bitboard())) {
            if (move.from == -1) {
                move.from = square_clicked;
                std::cout << "Changed from\n";
            } else if (move.from != square_clicked) {
                std::cout << "Changed to\n";
                move.to = square_clicked;
                current_position = current_position.move(move);
            }
        }
    }
}


void GameState::render() {
    draw_board();
    draw_pieces();
}

void GameState::handle_events() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!pressed) {
            pressed = true;
            clicked_square();
        }
    } else {
        pressed = false;
    }
}

void GameState::update() {

}



