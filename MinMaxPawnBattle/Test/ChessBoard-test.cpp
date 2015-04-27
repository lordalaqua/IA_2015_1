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
    CHECK(board.occupied() == 5399552071500349258);
    CHECK(board(Piece::WHITE) == 1073790794);
    CHECK(board(Piece::BLACK) == 5399552070426558464);
}

TEST(ChessBoardCountingTest)
{
    std::string board_str =
        ".n.q..n."
        "pppp.ppp"
        ".p..p.p."
        "........"
        "..P...P."
        "P......."
        "PPPPPP.P"
        ".N.Q..N.";

    ChessBoard board(board_str);
    CHECK(board.countPieces(Piece::BLACK, Piece::PAWN) == 10);
    CHECK(board.countPieces(Piece::WHITE, Piece::PAWN) == 10);
    CHECK(board.countPieces(Piece::BLACK, Piece::KNIGHT) == 2);
    CHECK(board.countPieces(Piece::WHITE, Piece::KNIGHT) == 2);
    CHECK(board.countPieces(Piece::BLACK, Piece::QUEEN) == 1);
    CHECK(board.countPieces(Piece::WHITE, Piece::QUEEN) == 1);
    CHECK(board.countPieces(Piece::BLACK) == 13);
    CHECK(board.countPieces(Piece::WHITE) == 13);
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

    // Array to keep which results were found
    bool found[6] = { false, false, false, false, false, false };

    // White and Black pawn boards with desired output, the plays are the following:
    // 0 - Push of lower white pawn
    // 1 - Push of upper white pawn
    // 2 - Double Push of lower white pawn
    // 3 - Lower white pawn captures to the right
    // 4 - Upper white pawn captures to the left
    // 5 - Upper white pawn captures to the right
    unsigned long long int white[6] = { 1114112, 268435712, 17825792, 1179648, 134217984, 536871168 };
    unsigned long long int black[6] = { 671229952, 671229952, 671229952, 671098880, 537012224, 134359040 };

    CHECK(boards.size() == 6);

    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
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
        CHECK(found[i]); // Check if all desired results were found
    }
}

TEST(KnightMoveGenerationTest)
{
    std::string board_str =
        "........"
        "........"
        "........"
        "........"
        "........"
        "........"
        "........"
        "........";

    ChessBoard board(board_str);
    auto boards = board.generateMoves(Piece::BLACK);

    /*// Array to keep which results were found
    bool found[6] = { false, false, false, false, false, false };
    unsigned long long int white[6] = { 1114112, 268435712, 17825792, 1179648, 134217984, 536871168 };
    unsigned long long int black[6] = { 671229952, 671229952, 671229952, 671098880, 537012224, 134359040 };

    CHECK(boards.size() == 6);

    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
        for (int i = 0; i < 6; ++i)
        {
            if (!found[i] &&
                b(Piece::WHITE, Piece::KNIGHT) == white[i] &&
                b(Piece::BLACK, Piece::KNIGHT) == black[i])
            {
                found[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        CHECK(found[i]); // Check if all desired results were found
    }*/
}

