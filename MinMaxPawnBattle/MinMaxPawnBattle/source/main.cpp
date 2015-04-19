#include <iostream>
#include "RandomBot.hpp"

int main(int argc, char** argv)
{
    int port = 50100;
    std::string name = "TestBot";
    if (argc > 1)
    {
        port = atoi(argv[1]);
        if (argc > 2) 
            name = argv[2];
    }
    RandomBot bot;
    bot.run(name, port);
}