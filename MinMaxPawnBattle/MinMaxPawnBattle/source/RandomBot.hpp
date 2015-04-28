#ifndef RandomBot_h__
#define RandomBot_h__
#include "LiacBot.hpp"

/* Bot that chooses one of all possible moves at random. */

class RandomBot : public LiacBot
{
public:
    RandomBot();
private:
    virtual void onMove(BoardState state) override;
    virtual void onGameOver(BoardState state) override;
};

#endif // RandomBot_h__