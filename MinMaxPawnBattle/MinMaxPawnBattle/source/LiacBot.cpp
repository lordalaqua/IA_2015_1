#include "LiacBot.hpp"

bool LiacBot::run(std::string name /*= "NamelessBot"*/, int port /*= 50100*/, std::string ip /*= "127.0.0.1"*/)
{
    name_ = name;
    connectTCPSocket(port, ip);
    sendName();
    while (receiveState())
    {
        if (state_.winner != 0 || state_.draw)
        {
            onGameOver(state_);
            return true;
        }
        else
        {
            onMove(state_);
        }        
    }
    return false;
}

bool LiacBot::sendMove(std::pair<int, int> from, std::pair<int, int> to)
{
    std::stringstream ss;
    ss << "{\"from\":[" << from.first << "," << from.second << "],";
    ss << "\"to\":[" << to.first << "," << to.second << "]}";
    if (send(tcp_socket_, ss.str().c_str(), sizeof(char)*ss.str().size(), 0) < 0)
    {
        closesocket(tcp_socket_);
        return false;
    }
    return true;
}

bool LiacBot::sendName()
{
    std::string message = "{\"name\":\"" + name_ + "\"}";
    if (send(tcp_socket_, message.c_str(), sizeof(char)*message.size(), 0) < 0)
    {
        closesocket(tcp_socket_);
        return false;
    }
    else
    {
        return true;
    }    
}

bool LiacBot::receiveState()
{
    char receive_buffer[BUFFER_SIZE];
    if ((recv(tcp_socket_, receive_buffer, BUFFER_SIZE, 0)) < 0)
    {
        closesocket(tcp_socket_);
        return false;
    }
    else
    {
        std::stringstream ss(receive_buffer);
        std::string state_json;
        std::getline(ss, state_json, '}');
        state_.parse(state_json + "}");
        return true;
    }
}

bool LiacBot::connectTCPSocket(int server_port, std::string server_ip, int client_port /*= 0*/)
{
    // Start up winsock2 library (windows only)
    WSADATA winsock_info;
    if (WSAStartup(MAKEWORD(2, 2), &winsock_info) != 0)
        return false;

    // Open TCP socket
    if ((tcp_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        return false;

    // Set local IP/port info
    SocketAddressIn client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (client_port == LiacBot::DEFAULT_CLIENT) 
        client_port = server_port - 1;
    client_address.sin_port = htons(client_port);

    // Bind local configuration to socket
    if (bind(tcp_socket_, (SocketAddress *)&client_address, sizeof(client_address)) != 0)
    {
        closesocket(tcp_socket_);
        return false;
    }

    // Set remote server IP/port info
    SocketAddressIn server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    server_address.sin_port = htons(server_port);

    // Connect client socket with server
    if (connect(tcp_socket_, (SocketAddress*)&server_address, sizeof(server_address)) != 0)
    {
        closesocket(tcp_socket_);
        return false;
    }

    // No errors occurred
    return true;
}
