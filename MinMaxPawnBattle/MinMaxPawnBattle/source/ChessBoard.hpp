#ifndef CHESSBOARD_HPP_
#define CHESSBOARD_HPP_

#include <bitset>
#include "Piece.hpp"
#include "BoardState.hpp"

// Chess Board representation, since we are playing Battle of the Pawns, some
// pieces are not needed.

class ChessBoard
{
public:
    ChessBoard() {};
    ChessBoard(const BoardState& state);
    ~ChessBoard() {};

public:
    static const int BOARD_SIZE = 64;
    const std::bitset<BOARD_SIZE>& black(Piece::Type type) { return black_[type]; }
    const std::bitset<BOARD_SIZE>& white(Piece::Type type) { return white_[type]; }

private:
    std::bitset<BOARD_SIZE> black_[Piece::Type::TOTAL];
    std::bitset<BOARD_SIZE> white_[Piece::Type::TOTAL];

};

#endif /*CHESSBOARD_HPP_*/