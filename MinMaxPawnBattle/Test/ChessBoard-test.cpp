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

TEST(WhitePawnMoveGenerationTest)
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

    // Test White Piece Move generation
    auto boards = board.generateMoves(Piece::WHITE);
    const int output_size = 6;
    // Array to keep which results were found
    bool found[output_size] = { false };

    // White and Black pawn boards with desired output, the plays are the following:
    unsigned long long int white[output_size] = { 
        1114112,    // 0 - Lower white pawn Push
        268435712,  // 1 - Upper white pawn Push
        17825792,   // 2 - Lower white pawn Double Push 
        1179648,    // 3 - Lower white pawn captures to the right
        134217984,  // 4 - Upper white pawn captures to the left
        536871168   // 5 - Upper white pawn captures to the right
    };
    unsigned long long int black[output_size] = { 
        671229952,  // 0 - Lower white pawn Push
        671229952,  // 1 - Upper white pawn Push
        671229952,  // 2 - Lower white pawn Double Push 
        671098880,  // 3 - Lower white pawn captures to the right
        537012224,  // 4 - Upper white pawn captures to the left
        134359040   // 5 - Upper white pawn captures to the right
    };

    CHECK(boards.size() == output_size);

    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
        for (int i = 0; i < output_size; ++i)
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
    for (int i = 0; i < output_size; ++i)
    {
        CHECK(found[i]); // Check if all desired results were found
    }
}

TEST(BlackPawnMoveGenerationTest)
{
    std::string board_str =
        "........"
        "p......."
        ".P......"
        "........"
        "...p.p.."
        "....P..."
        "........"
        "........";
    ChessBoard board(board_str);
    // Test White Piece Move generation
    auto boards = board.generateMoves(Piece::BLACK);

    const int output_size = 7;
    // Array to keep which results were found
    bool found[output_size] = { false };

    // White and Black pawn boards with desired output, the plays are the following:
    unsigned long long int black[output_size] = { 
        1100182716416,      // 0 - Upper black pawn Push
        4966055936,         // 1 - Upper black pawn Double Push 
        2199694344192,      // 2 - Upper black pawn captures to the right
        281475514105856,    // 3 - Left Lower black pawn Push 
        281475514630144,    // 4 - Left Lower black pawn Capture
        281475113025536,    // 5 - Right Lower black pawn Push    
        281475111976960     // 6 - Right Lower black pawn Capture
    };
    unsigned long long int white[output_size] = { 
        2199024304128,      // 0 - Upper black pawn Push
        2199024304128,      // 1 - Upper black pawn Double Push 
        1048576,            // 2 - Upper black pawn captures to the right
        2199024304128,      // 3 - Left Lower black pawn Push 
        2199023255552,      // 4 - Left Lower black pawn Capture
        2199024304128,      // 5 - Right Lower black pawn Push  
        2199023255552       // 6 - Right Lower black pawn Capture
    };

    CHECK(boards.size() == output_size);

    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
        for (int i = 0; i < output_size; ++i)
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
    for (int i = 0; i < output_size; ++i)
    {
        CHECK(found[i]); // Check if all desired results were found
    }
}

TEST(KnightMoveGenerationTest)
{
    std::string board_str =
        "N......."
        "..n....."
        "........"
        "........"
        "........"
        "P...p..."
        "..N....."
        "........";
    549755814912;
    70368744178688;
    4611686018427388928;
    ChessBoard board(board_str);
    auto boards = board.generateMoves(Piece::WHITE);
    const int knight_moves = 7;
    unsigned long long int white_knights[knight_moves] = {
        // 72057594037928960  Initial Board
        72057594037927937,   // 0 - Lower white knight to -1,-2 (y,x)
        72057594037927952,   // 1 - Lower white knight to -1,+2 (y,x)
        72057594038976512,   // 2 - Lower white knight to +1,+2 (y,x)
        72057594071482368,   // 3 - Lower white knight to +2,-1 (y,x)
        72057594172145664,   // 4 - Lower white knight to +2,+1 (y,x)
        1125899906843648,    // 5 - Upper white knight to -1,+2 (y,x)
        2199023256576        // 6 - Lower white knight to -2,+1 (y,x)
    };
    unsigned long long int black_knights[knight_moves];
    unsigned long long int white_pawns[knight_moves];
    unsigned long long int black_pawns[knight_moves];
    for (int i = 0; i < knight_moves; ++i)
    {
        // Other pieces hold same position for most cases
        black_knights[i] = 1125899906842624;
        white_pawns[i] = 65536;
        black_pawns[i] = 1048576;
    }
    black_knights[5] = 0;   // black knight captured in move 5
    black_pawns[2] = 0;     // black pawn captured in move 2

    CHECK(boards.size() == knight_moves+1);
    // Array to keep which results were found
    bool found[knight_moves] = { false };
    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
        for (int i = 0; i < knight_moves; ++i)
        {
            if (!found[i] &&
                b(Piece::WHITE, Piece::KNIGHT) == white_knights[i] &&
                b(Piece::BLACK, Piece::KNIGHT) == black_knights[i] &&
                b(Piece::WHITE, Piece::PAWN) == white_pawns[i] &&
                b(Piece::BLACK, Piece::PAWN) == black_pawns[i])
            {
                found[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < knight_moves; ++i)
    {
        CHECK(found[i]); // Check if all desired results were found
    }
}

TEST(QueenMoveGenerationTest)
{
    std::string board_str =
        ".q......"
        "........"
        "...p...."
        "........"
        ".Q..P..."
        ".P......"
        "........"
        "........";

    ChessBoard board(board_str);
    auto boards = board.generateMoves(Piece::WHITE);
    const int queen_moves = 14;
    unsigned long long int white_queen[queen_moves] = {
        // 33554432 - Initial Position (3,1)
        8589934592,             // 0 - (4,1) - N
        2199023255552,          // 1 - (5,1)
        562949953421312,        // 2 - (6,1)
        144115188075855872,     // 3 - (7,1)

        17179869184,            // 4 - (4,2) - NE
        8796093022208,          // 5 - (5,3)

        67108864,               // 6 - (3,2) - E
        134217728,              // 7 - (3,3)

        262144,                 // 8 - (2,2) - SE
        2048,                   // 9 - (1,3)
        16,                     //10 - (0,4)

        65536,                  //11 - (2,0) - SW

        16777216,               //12 - (3,0) - W

        4294967296              //13 -  (4,0) - NW
    };
    unsigned long long int black_queen[queen_moves];
    unsigned long long int white_pawns[queen_moves];
    unsigned long long int black_pawns[queen_moves];
    for (int i = 0; i < queen_moves; ++i)
    {
        // Other pieces hold same position for most cases
        black_queen[i] = 144115188075855872;
        white_pawns[i] = 268566528;
        black_pawns[i] = 8796093022208;
    }
    black_queen[3] = 0;     // black queen captured in move 3
    black_pawns[5] = 0;     // black pawn captured in move 5

    CHECK(boards.size() == queen_moves + 1);

    // Array to keep which results were found
    bool found[queen_moves] = { false };
    for (const auto& b : boards)
    {
        // for each result board, find it in the desired output arrays
        for (int i = 0; i < queen_moves; ++i)
        {
            if (!found[i] &&
                b(Piece::WHITE, Piece::QUEEN) == white_queen[i] &&
                b(Piece::BLACK, Piece::QUEEN) == black_queen[i] &&
                b(Piece::WHITE, Piece::PAWN) == white_pawns[i] &&
                b(Piece::BLACK, Piece::PAWN) == black_pawns[i])
            {
                found[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < queen_moves; ++i)
    {
        CHECK(found[i]); // Check if all desired results were found
    }
}