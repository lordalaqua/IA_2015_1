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
};

#endif // Piece_h__
