#pragma comment(lib, "ws2_32.lib")

#include<winsock2.h>
#include<iostream>

SOCKET newConnection;

void ClientHandler() {
    char msg[256];
    while (true) {
        recv(newConnection, msg, sizeof(msg), NULL);
        std::cout << msg << "\n";
    }
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    WORD minVersion = MAKEWORD(2, 2);
    if (WSAStartup(minVersion, &wsaData) != 0) {
        std::cout << "Error.1\n";
        return 1;
    }

    SOCKADDR_IN addr;
    int sz = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(11111);
    addr.sin_family = AF_INET;

    newConnection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(newConnection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error.2\n";
    }

    std::cout << "Connected!\n";
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

    char msg[256];
    while (true) {
        std::cin.getline(msg, sizeof(msg));
        send(newConnection, msg, sizeof(msg), NULL);
        Sleep(10);
    }

    return 0;
}