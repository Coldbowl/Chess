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

    PieceInfo white_pieces[6] = {
        { &white_king_sprite, &Position::get_white_king_bitboard, true },
        { &white_queen_sprite, &Position::get_white_queen_bitboard, false },
        { &white_bishop_sprite, &Position::get_white_bishop_bitboard, false },
        { &white_knight_sprite, &Position::get_white_knight_bitboard, false },
        { &white_rook_sprite, &Position::get_white_rook_bitboard, false },
        { &white_pawn_sprite, &Position::get_white_pawn_bitboard, false }
    };

    PieceInfo black_pieces[6] = {
        { &black_king_sprite, &Position::get_black_king_bitboard, true },
        { &black_queen_sprite, &Position::get_black_queen_bitboard, false },
        { &black_bishop_sprite, &Position::get_black_bishop_bitboard, false },
        { &black_knight_sprite, &Position::get_black_knight_bitboard, false },
        { &black_rook_sprite, &Position::get_black_rook_bitboard, false },
        { &black_pawn_sprite, &Position::get_black_pawn_bitboard, false }
    };


public:
    explicit GameState(Engine* engine, sf::RenderWindow& window);

    void draw_board() const;

    void draw_pieces();

    void update() override;
    void render() override;
    void handle_events() override;
};