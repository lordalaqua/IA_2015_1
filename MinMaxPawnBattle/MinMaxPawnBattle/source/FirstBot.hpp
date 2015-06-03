#ifndef FirstBot_h__
#define FirstBot_h__
#include "LiacBot.hpp"
#include "Piece.hpp"
#include "ChessBoard.hpp"
#include <limits>
#include <algorithm>

class FirstBot : public LiacBot
{
    struct Play
    {
        Play(int s, std::pair<int, int> f, std::pair<int, int> t) 
        : score(s), from(f), to(t) {};
        int score;
        std::pair<int, int> from;
        std::pair<int, int> to;
    };
public:
    FirstBot(int depth = 3) : depth_(depth) {}
private:
    virtual void onMove(BoardState state) override;
    virtual void onGameOver(BoardState state) override;
    Play negamax(const ChessBoard& node, int depth, int color, Piece::Color team, int alpha, int beta);
private:
    Piece::Color team_;
    int depth_;
    const int INF = std::numeric_limits<int>::max()-1;
};


#endif // FirstBot_h__