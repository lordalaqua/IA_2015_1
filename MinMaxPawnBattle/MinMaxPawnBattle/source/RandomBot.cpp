#include "RandomBot.hpp"
#include "ChessBoard.hpp"
#include <cstdlib>
#include <ctime>


RandomBot::RandomBot() : LiacBot()
{
    srand(time(NULL)); // initialize RNG seed
}

void RandomBot::onMove(BoardState state)
{
    ChessBoard board(state.board);
    Piece::Color team = Piece::findTeam(state.who_moves);
    auto moves = board.generateMoves(team); // generate all possible moves

    // Print debug messages
    int infractions = team == Piece::WHITE ? state.white_infractions : state.black_infractions;    
    std::cout << moves.size() << " moves," << infractions << " infractions" << std::endl;

    // Print board
    std::bitset<64> bitboard = board.occupied();
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 8; ++j)
        {
            std::cout << bitboard[j + 8 * i] << " ";
        }
        std::cout << std::endl;
    }
    
    // Send move and print if succesful
    int chosen_move = rand() % moves.size();
    if (!sendMove(moves[chosen_move].from(), moves[chosen_move].to()))
    {
        std::cout << "Failed to send move" << std::endl;
    }
    else
    {
        std::cout << "Sent move: ";
        std::cout << "(" << moves[chosen_move].from().first << "," << moves[chosen_move].from().second << ") to ";
        std::cout << "(" << moves[chosen_move].to().first << "," << moves[chosen_move].to().second << ")" << std::endl;
    }
}

void RandomBot::onGameOver(BoardState state)
{
    Piece::Color team = Piece::findTeam(state.who_moves);
    if (state.draw)
        std::cout << "DRAW! Boooring!" << std::endl;
    else if (Piece::findTeam(state.winner) == team)
        std::cout << "YOU RANDOMLY WON! CONGRATULATIONS!" << std::endl;
    else
        std::cout << "YOU LOSE! It's random anyway..." << std::endl;
}
