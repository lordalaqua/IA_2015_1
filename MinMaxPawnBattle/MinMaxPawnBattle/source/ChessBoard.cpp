#include "ChessBoard.hpp"
#include "BitOperations.hpp"


ChessBoard::ChessBoard(const std::string& board)
{
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
    {
        board_[Piece::WHITE][i] = 0;
        board_[Piece::BLACK][i] = 0;
    }
    int i = 7, j = 0; // strange configuration in the string
    for (char tile : board)
    {
        switch (tile)
        {
        case 'p':
            board_[Piece::BLACK][Piece::PAWN][j + i * 8] = 1;
            break;
        case 'P':
            board_[Piece::WHITE][Piece::PAWN][j + i * 8] = 1;
            break;
        case 'n':
            board_[Piece::BLACK][Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'N':
            board_[Piece::WHITE][Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'q': // Queen
            board_[Piece::BLACK][Piece::QUEEN][j + i * 8] = 1;
            break;
        case 'Q':
            board_[Piece::WHITE][Piece::QUEEN][j + i * 8] = 1;
            break;
        // default: leave boards as zero, unoccupied
        }
        // Move to next tile
        if (j < 7)
        {
            ++j;
        }
        else
        {
            j = 0;
            i -= 1;
        }
    }
    from_ = { 0, 0 };
    to_ = from_;
}

std::vector<ChessBoard> ChessBoard::generateMoves(Piece::Color team)
{
    std::vector<ChessBoard> moves;
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
        generateMovesFor((Piece::Type)i, team, moves);
    return moves;
}

void ChessBoard::generateMovesFor(Piece::Type type, Piece::Color team, const std::vector<ChessBoard>& moves)
{
    switch (type)
    {
    case Piece::PAWN:
        generatePawnMoves(team, moves);
        break;
    case Piece::KNIGHT:
        generateKnightMoves(team, moves);
        break;
    case Piece::QUEEN:
        generateQueenMoves(team, moves);
        break;
    }
}

void ChessBoard::generatePawnMoves(Piece::Color team, const std::vector<ChessBoard>& moves)
{
    uint64 to_move = board_[team][Piece::PAWN].to_ullong();
}

void ChessBoard::generateKnightMoves(Piece::Color team, const std::vector<ChessBoard>& moves)
{

}

void ChessBoard::generateQueenMoves(Piece::Color team, const std::vector<ChessBoard>& moves)
{

}
