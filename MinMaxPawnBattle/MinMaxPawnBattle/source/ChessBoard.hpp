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
public:
    ChessBoard() {};
    ChessBoard(const ChessBoard& other);
    ChessBoard(const std::string& board);
    std::vector<ChessBoard> generateMoves(Piece::Color team) const;
    int materialEvaluation(Piece::Color team, int queen_weight = 1,
        int knight_weight = 1, int pawn_weight = 5) const;
    int positionEvaluation(Piece::Color team) const;
    int endGameTest() const;
    const std::bitset<64>& operator()(Piece::Color color, Piece::Type type) const;
    std::bitset<64> operator()(Piece::Color color) const;
    int countPieces(Piece::Color color, Piece::Type type) const;
    int countPieces(Piece::Color color) const;
    std::bitset<64> occupied() const;
    std::pair<int, int> from() const { return from_; }
    std::pair<int, int> to() const { return to_; }
private:
    void generatePawnMoves(Piece::Color team, std::vector<ChessBoard>& moves) const;
    void generateKnightMoves(Piece::Color team, std::vector<ChessBoard>& moves) const;
    void generateQueenMoves(Piece::Color team, std::vector<ChessBoard>& moves) const;
    ChessBoard& makeMove(Piece::Color team, Piece::Type type, int from, int to);
    ChessBoard& makeCapture(Piece::Color team, Piece::Type type, int from, int to);
    void setFromTo(int from, int to);
private:
    std::bitset<64> board_[Piece::NUM_COLORS][Piece::NUM_TYPES];
    std::pair<int, int> from_;
    std::pair<int, int> to_;
};

#endif /*CHESSBOARD_HPP_*/