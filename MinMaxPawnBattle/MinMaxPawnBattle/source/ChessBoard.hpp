#ifndef CHESSBOARD_HPP_
#define CHESSBOARD_HPP_

#include <bitset>
#include <vector>
#include <cassert>
#include "Piece.hpp"

// Chess Board representation, since we are playing Battle of the Pawns, some
// pieces are not needed.

class ChessBoard
{
private:
    static const int BOARD_SIZE = 64;
public:
    ChessBoard(const ChessBoard& other) 
    {
        for (int i = 0; i < Piece::NUM_COLORS; ++i)
        {
            for (int j = 0; j < Piece::NUM_TYPES; ++j)
            {
                board_[i][j] = other.board_[i][j];
            }
        }
    };
    ChessBoard(const std::string& board);
    std::vector<ChessBoard> generateMoves(Piece::Color team);
    
    const std::bitset<BOARD_SIZE>& operator()(Piece::Color color, Piece::Type type) const { return board_[color][type]; }
private:
    void generateMovesFor(Piece::Type type, Piece::Color team, const std::vector<ChessBoard>& moves);
    void generatePawnMoves(Piece::Color team, const std::vector<ChessBoard>& moves);
    void generateKnightMoves(Piece::Color team, const std::vector<ChessBoard>& moves);
    void generateQueenMoves(Piece::Color team, const std::vector<ChessBoard>& moves);
private:
    std::bitset<BOARD_SIZE> board_[Piece::NUM_COLORS][Piece::NUM_TYPES];
    std::pair<int, int> from_;
    std::pair<int, int> to_;
    static const int BITSCAN_INDEX[64];
};

#endif /*CHESSBOARD_HPP_*/