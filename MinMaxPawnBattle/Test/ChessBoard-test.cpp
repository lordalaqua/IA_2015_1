#include <UnitTest++.h>
#include "ChessBoard.hpp"

TEST(ChessBoardInitializeTest)
{
    std::string json =
        "{ "
        "\"board\" : \".n.q..n.pppp.ppp....p...........................PPPPPPPP.N.Q..N.\","
        "\"enpassant\" : [[2,1],[3,1], [ 5 , 2  ] , [6,3]], "
        "\"who_moves\" : -1, "
        "\"bad_move\" : false, "
        "\"black_infractions\" : 20 , "
        "\"winner\" : -1,"
        "\"50moves\" : true,"
        "\"draw\" : false ,"
        "\"white_infractions\" : 10"
        "}";

    BoardState state(json);

    ChessBoard board(state);
    CHECK(board.black(Piece::QUEEN) == 576460752303423488);
    CHECK(board.black(Piece::KNIGHT) == 4755801206503243776);
    CHECK(board.black(Piece::PAWN) == 67290111619891200);//71776119061217280);
    CHECK(board.white(Piece::QUEEN) == 8);
    CHECK(board.white(Piece::KNIGHT) == 66);
    CHECK(board.white(Piece::PAWN) == 65280);
}

