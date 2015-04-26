#include <UnitTest++.h>
#include "ChessBoard.hpp"
#include <iostream>

TEST(ChessBoardInitializeTest)
{
    std::string board_str =
        ".n.q..n."
        "pppp.ppp"
        "....p..."
        "........"
        "......P."
        "........"
        "PPPPPP.P"
        ".N.Q..N.";

    ChessBoard board(board_str);
    CHECK(board(Piece::BLACK,Piece::QUEEN) == 576460752303423488);
    CHECK(board(Piece::BLACK, Piece::KNIGHT) == 4755801206503243776);
    CHECK(board(Piece::BLACK,Piece::PAWN) == 67290111619891200);
    CHECK(board(Piece::WHITE, Piece::QUEEN) == 8);
    CHECK(board(Piece::WHITE, Piece::KNIGHT) == 66);
    CHECK(board(Piece::WHITE, Piece::PAWN) == 1073790720);
}

TEST(PawnMoveGenerationTest)
{
    std::string board_str =
        "........"
        "........"
        "........"
        "........"
        "...p.p.."
        ".p..P..."
        "P..p.p.."
        "........";

    ChessBoard board(board_str);
    auto boards = board.generateMoves(Piece::WHITE);
    bool found[6] = { false, false, false, false, false, false };
    unsigned long long int white[6] = { 1114112, 268435712, 1179648, 134217984, 536871168 };
    unsigned long long int black[6] = { 671229952, 671229952, 671229952, 671098880, 537012224, 134359040 };

    CHECK(boards.size() == 6);

    for (const auto& b : boards)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (!found[i] && 
                b(Piece::WHITE, Piece::PAWN) == white[i] && 
                b(Piece::BLACK, Piece::PAWN) == black[i])
            {
                found[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        CHECK(found[i]);
    }
}

