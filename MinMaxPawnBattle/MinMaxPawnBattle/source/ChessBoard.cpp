#include "ChessBoard.hpp"


ChessBoard::ChessBoard(const BoardState& state)
{
    for (int i = 0; i < Piece::Type::TOTAL; ++i)
    {
        white_[i] = 0;
        black_[i] = 0;
    }
    int i = 7, j = 0; // strange configuration in the string
    for (char tile : state.board)
    {
        switch (tile)
        {
        case 'p':
            black_[Piece::PAWN][j + i * 8] = 1;
            break;
        case 'P':
            white_[Piece::PAWN][j + i * 8] = 1;
            break;
        case 'n':
            black_[Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'N':
            white_[Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'q': // Queen
            black_[Piece::QUEEN][j + i * 8] = 1;
            break;
        case 'Q':
            white_[Piece::QUEEN][j + i * 8] = 1;
            break;
        // default: leave boards as zero, unoccupied
        // TODO: K,k,B,b,R,r for king, bishop and rook
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
}
