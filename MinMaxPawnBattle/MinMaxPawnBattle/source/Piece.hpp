#ifndef Piece_h__
#define Piece_h__

class Piece
{
public:
    enum Type
    {
        PAWN = 0,
        KNIGHT,
        //TOWER,    // not used in pawn battle to be played
        //BISHOP,   // not used in pawn battle to be played
        QUEEN,
        //KING      // not used in pawn battle to be played
        TOTAL
    };
    enum Color
    {
        BLACK,
        WHITE
    };
public:
    Color color;
    Type type;
};

#endif // Piece_h__
