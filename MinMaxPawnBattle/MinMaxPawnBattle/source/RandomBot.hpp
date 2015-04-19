#pragma once
#include "LiacBot.hpp"

/* Bot that chooses one of possible moves at random. */

class RandomBot : public LiacBot
{
public:
    RandomBot();
    ~RandomBot();

private:
    virtual void onMove(BoardState state) override;
    virtual void onGameOver(BoardState state) override;
};

