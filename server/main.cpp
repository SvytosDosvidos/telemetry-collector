#pragma comment(lib, "ws2_32.lib")

#include<winsock2.h>
#include<iostream>

SOCKET Connections[100];
int Counter = 0;

void ClientHandlet(int index) {
    char msg[256];
    while (true) {
        recv(Connections[index], msg, sizeof(msg), NULL);
        for (int i = 0; i < Counter; i++) {
            if (i == index) {
                continue;
            }

            send(Connections[i], msg, strlen(msg), NULL);
        }
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

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sz);
        if (newConnection == 0) {
            std::cout << "Error.2\n";
        } else {
            std::cout << "Connect!\n";

            Connections[i] = newConnection;
            Counter++;
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlet, (LPVOID)(i), NULL, NULL);
        }
    }

    return 0;
}