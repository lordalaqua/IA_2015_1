#ifndef BOARDSTATE_HPP_
#define BOARDSTATE_HPP_

#include <string>
#include <vector>
#include <sstream>

class BoardState
{
public:
    BoardState() { /*empty state*/ };
    BoardState(std::string json);
    void parse(std::string json);

public: // fields
    std::string board;
    std::vector<std::pair<int, int>> enpassant;
    int who_moves;
    bool bad_move;
    int white_infractions;
    int black_infractions;
    int winner;
    bool fifty_moves;
    bool draw;
};


#endif