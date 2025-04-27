#include "server.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <thread>
#include <fstream>
#include <sstream>

Server::Server(int port) : port_(port) {}

void Server::start() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    int c;

    std::cout << "[*] Starting server on port " << port_ << "...\n";

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "[-] Winsock initialization failed. Error Code: " << WSAGetLastError() << std::endl;
        return;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "[-] Could not create socket. Error Code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_);

    if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "[-] Bind failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    listen(serverSocket, 5);
    std::cout << "[*] Waiting for incoming connections...\n";

    c = sizeof(struct sockaddr_in);

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "[-] Accept failed. Error Code: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "[+] Connection accepted! Launching thread...\n";

        // Spawn a new thread for each client
        std::thread(&Server::handleClient, this, clientSocket).detach();
    }

    closesocket(serverSocket);
    WSACleanup();
}

void Server::handleClient(SOCKET clientSocket) {
    // Buffer to receive request
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
        std::cerr << "[-] Failed to receive data or client disconnected.\n";
        closesocket(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0'; // Null terminate the received data
    std::cout << "[*] Request received:\n" << buffer << "\n";

    // Always serve "index.html" for now
    std::ifstream file("www/index.html", std::ios::binary);

    if (!file.is_open()) {
        // If file not found, send 404
        const char* notFound =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: 48\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>";

        send(clientSocket, notFound, strlen(notFound), 0);
        shutdown(clientSocket, SD_SEND);
        closesocket(clientSocket);
        std::cout << "[-] 404 Not Found sent.\n";
        return;
    }

    // Read file into string
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string body = ss.str();
    file.close();

    // Build headers
    std::string headers =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n";

    // Full response
    std::string response = headers + body;

    // Send response
    int totalSent = 0;
    int toSend = response.size();
    while (totalSent < toSend) {
        int sent = send(clientSocket, response.c_str() + totalSent, toSend - totalSent, 0);
        if (sent == SOCKET_ERROR) {
            std::cerr << "[-] Send failed. Error code: " << WSAGetLastError() << "\n";
            break;
        }
        totalSent += sent;
    }

    shutdown(clientSocket, SD_SEND);
    closesocket(clientSocket);

    std::cout << "[*] Client served and connection closed.\n";
}

