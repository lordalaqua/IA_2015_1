#ifndef Piece_h__
#define Piece_h__

namespace Piece
{
    enum Type
    {
        PAWN = 0,
        KNIGHT,
        QUEEN,
        NUM_TYPES
    };
    enum Color
    {
        BLACK = 0,
        WHITE,
        NUM_COLORS
    };

    inline Color otherTeam(Color t) { return t == BLACK ? WHITE : BLACK; }

    // Converts LiacChess team to Piece::Color value
    inline Color intToColor(int t) { return (t == 1) ? WHITE : BLACK; }
    inline int colorToInt(Color c) { return (c == WHITE) ? 1 : -1; }
};

#endif // Piece_h__
