#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "state.hpp"
#include "../Chess/Position.hpp"


struct PieceInfo {
    sf::Sprite* sprite;
    uint64_t (Position::*getter)() const; // pointer to member function
    bool single; // true for king
};

namespace sf { class RenderWindow; }

class GameState final : public State {
    bool is_player_white;

    bool pressed = false;
    sf::Vector2i mouse_position;

    Move move;

    sf::RenderWindow& window;

    sf::Texture pieces_texture;

    sf::Sprite white_pawn_sprite;
    sf::Sprite white_rook_sprite;
    sf::Sprite white_knight_sprite;
    sf::Sprite white_bishop_sprite;
    sf::Sprite white_queen_sprite;
    sf::Sprite white_king_sprite;

    sf::Sprite black_pawn_sprite;
    sf::Sprite black_rook_sprite;
    sf::Sprite black_knight_sprite;
    sf::Sprite black_bishop_sprite;
    sf::Sprite black_queen_sprite;
    sf::Sprite black_king_sprite;

    Position current_position;

    PieceInfo white_bitboards[6] = {
        { &white_pawn_sprite,   &Position::get_white_pawn_bitboard,   false },
        { &white_knight_sprite, &Position::get_white_knight_bitboard, false },
        { &white_bishop_sprite, &Position::get_white_bishop_bitboard, false },
        { &white_rook_sprite,   &Position::get_white_rook_bitboard,   false },
        { &white_queen_sprite,  &Position::get_white_queen_bitboard,  false },
        { &white_king_sprite,   &Position::get_white_king_bitboard,   true  }
    };


    PieceInfo black_bitboards[6] = {
        { &black_pawn_sprite,   &Position::get_black_pawn_bitboard,   false },
        { &black_knight_sprite, &Position::get_black_knight_bitboard, false },
        { &black_bishop_sprite, &Position::get_black_bishop_bitboard, false },
        { &black_rook_sprite,   &Position::get_black_rook_bitboard,   false },
        { &black_queen_sprite,  &Position::get_black_queen_bitboard,  false },
        { &black_king_sprite,   &Position::get_black_king_bitboard,   true  }
    };

public:
    explicit GameState(Engine* engine, sf::RenderWindow& window, bool is_player_white);

    void draw_board() const;

    void draw_pieces() const;

    void clicked_square();

    void update() override;
    void render() override;
    void handle_events() override;
};