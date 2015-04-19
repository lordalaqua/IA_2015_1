#ifndef LIACBOT_HPP_
#define LIACBOT_HPP_

#include <winsock2.h>
#include <string>
#include <sstream>
#include <iostream>
#include "BoardState.hpp"

// Alias winsock2 names to better conform with coding standards
typedef struct sockaddr_in SocketAddressIn;
typedef struct sockaddr SocketAddress;
typedef int Socket;

// Size of buffer to receive messages
const int BUFFER_SIZE = 1024; 

// abstract class
class LiacBot
{
// Interface
public:
    bool run(std::string name = "NamelessBot", int port = 50100, std::string ip = "127.0.0.1");
protected:
    bool sendMove(std::pair<int, int> from, std::pair<int, int> to);
private:
// Pure virtual methods
    virtual void onMove(BoardState state) = 0;
    virtual void onGameOver(BoardState state) = 0;
// Private Methods
    
    bool sendName();
    bool receiveState();
    bool connectTCPSocket(int server_port, std::string server_ip, int client_port = LiacBot::DEFAULT_CLIENT);

// Fields
protected:
    std::string name_;
private:
    Socket tcp_socket_;
    BoardState state_;
    static const int DEFAULT_CLIENT = 0;
};

#endif