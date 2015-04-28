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
    ChessBoard(const ChessBoard& other);
    ChessBoard(const std::string& board);
    std::vector<ChessBoard> generateMoves(Piece::Color team);
    int materialEvaluation(Piece::Color team);
    const std::bitset<64>& operator()(Piece::Color color, Piece::Type type) const;
    std::bitset<64> operator()(Piece::Color color) const;
    int countPieces(Piece::Color color, Piece::Type type);
    int countPieces(Piece::Color color);
    std::bitset<64> occupied() const;
    const std::pair<int, int>& from() { return from_; }
    const std::pair<int, int>& to() { return to_; }
private:
    void generatePawnMoves(Piece::Color team, std::vector<ChessBoard>& moves);
    void generateKnightMoves(Piece::Color team, std::vector<ChessBoard>& moves);
    void generateQueenMoves(Piece::Color team, std::vector<ChessBoard>& moves);
    ChessBoard& makeMove(Piece::Color team, Piece::Type type, int from, int to);
    ChessBoard& makeCapture(Piece::Color team, Piece::Type type, int from, int to);
    void setFromTo(int from, int to);
private:
    std::bitset<64> board_[Piece::NUM_COLORS][Piece::NUM_TYPES];
    std::pair<int, int> from_;
    std::pair<int, int> to_;
};

#endif /*CHESSBOARD_HPP_*/