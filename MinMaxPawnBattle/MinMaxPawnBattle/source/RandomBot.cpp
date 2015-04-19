#include "RandomBot.hpp"


RandomBot::RandomBot()
{
    // Perform any initialization needed.
}


RandomBot::~RandomBot()
{
    // empty for now
}

void RandomBot::onMove(BoardState state)
{
    /* Dummy test to check if moves are being sent to application. */
    const int WHITE = 1;
    if (state.who_moves == WHITE)
        sendMove({ 1, 0 }, { 2, 0 });
    else // BLACK
        sendMove({ 6, 0 }, { 4, 0 });

    // TODO: convert BoardState to ChessBoard representation and choose play at
    // random.

    // sendMove(from, to);
}

void RandomBot::onGameOver(BoardState state)
{
    // Print if won or lost.
}
