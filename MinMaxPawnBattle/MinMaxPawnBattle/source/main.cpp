#include <iostream>
#include "FirstBot.hpp"
#include "RandomBot.hpp"


int main(int argc, char** argv)
{
    int port = 50100;
    int depth = 5;
    std::string name = "LordBot";
    if (argc > 1)
    {
        port = atoi(argv[1]);
        if (argc > 2)
        {
            depth = atoi(argv[2]);
            if (argc > 3)
                name = argv[3];
        }
    }
    if (name == "random")
    {
        RandomBot bot;
        bot.run("RandomBot", port);
    }
    else
    {
        FirstBot bot(depth);
        bot.run(name, port);
    }    
}