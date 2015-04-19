#ifndef CHESSBOARD_HPP_
#define CHESSBOARD_HPP_

#include <bitset>
#include <vector>
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
    std::bitset<64> black_pawns;
    std::bitset<64> black_knights;
    //std::bitset<64> black_towers;
    //std::bitset<64> black_bishops;
    std::bitset<64> black_queen;
    //std::bitset<64> black_king;

	std::bitset<64> white_pawns;
	std::bitset<64> white_knights;
    //std::bitset<64> white_towers;
    //std::bitset<64> white_bishops;
	std::bitset<64> white_queen;
    //std::bitset<64> white_king;
};

#endif /*CHESSBOARD_HPP_*/