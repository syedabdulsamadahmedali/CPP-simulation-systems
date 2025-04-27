#pragma once
#include <winsock2.h> // <-- ADD THIS LINE!

class Server {
public:
    Server(int port);
    void start();
private:
    void handleClient(SOCKET clientSocket);
    int port_;
};
