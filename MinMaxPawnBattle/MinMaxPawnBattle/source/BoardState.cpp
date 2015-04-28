#include "BoardState.hpp"
#include <iostream>

BoardState::BoardState(std::string json)
{
    parse(json);
}

std::string trimSpace(std::string s)
{
    size_t first = s.find_first_not_of(" ");
    if (first != std::string::npos)
        s = s.substr(first);
    size_t last = s.find_last_not_of(" ");
    if (last != std::string::npos)
        s = s.substr(0, last + 1);
    return s;
}

std::string trimNotNumber(std::string s)
{
    size_t first = s.find_first_of("-0123456789");
    if (first != std::string::npos)
        s = s.substr(first);
    size_t last = s.find_last_of("-0123456789");
    if (last != std::string::npos)
        s = s.substr(0, last + 1);
    return s;
}


void BoardState::parse(std::string json)
{
    // Parse board state here
    std::stringstream ss(json);
    std::string name, value, trash;
    while (std::getline(ss,trash,'\"'))
    {
            std::string name;
            std::getline(ss, name, '\"');
            std::getline(ss, trash, ':');

            if (name == "board")
            {
                std::getline(ss, trash, '\"');
                std::getline(ss, board, '\"');
            }
            else if (name == "enpassant")
            {/*
                std::getline(ss, value, ',');
                if (value.find_first_of('[') == std::string::npos) // no braces in field, is null
                {
                   enpassant.clear();
                }                 
                else // found opening brace, it is a list
                {
                    bool list = false;
                    std::string v((value.begin()+value.find_first_of('[') + 1), value.end());
                    if (v.find_first_of('[') == std::string::npos)
                        list = true;
                    std::pair<int, int> coord;

                    // Read first element
                    coord.first = atoi(trimNotNumber(value).c_str());
                    std::getline(ss, value, ']');
                    coord.second = atoi(trimNotNumber(value).c_str());
                    enpassant.push_back(coord);

                    while (true)
                    {
                        // Keep reading while there are new elements
                        std::getline(ss, value, ',');
                        if (value.find_first_of(']') == std::string::npos) 
                        {
                        // No closing brace before next comma, list not finished
                            std::getline(ss, value, ',');
                            coord.first = atoi(trimNotNumber(value).c_str());
                            std::getline(ss, value, ']');
                            coord.second = atoi(trimNotNumber(value).c_str());
                            enpassant.push_back(coord);
                        }
                        else
                            break; // Closing brace found, list finished
                    }
                }*/
            }
            else // booleans or numbers
            {
                std::getline(ss, value, ',');
                value = trimSpace(value);
                if (name == "bad_move")
                    bad_move = (value == "true") ? true : false;
                else if (name == "50moves")
                    fifty_moves = (value == "true") ? true : false;
                else if (name == "draw")
                    draw = (value == "true") ? true : false;
                else // numbers
                {
                    value = trimNotNumber(value);
                    if (name == "who_moves")
                        who_moves = atoi(value.c_str());
                    else if (name == "white_infractions")
                        white_infractions = atoi(value.c_str());
                    else if (name == "black_infractions")
                        black_infractions = atoi(value.c_str());
                    else if (name == "winner")
                        winner = atoi(value.c_str());
                }                
            }
    }
}
