#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET) {
        return 1;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8070);
    
    if (bind(udpSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(udpSocket);
        WSACleanup();
        return 1;
    }
    u_long mode = 1; // 1 to enable non-blocking mode
    ioctlsocket(udpSocket, FIONBIO, &mode);

    char buffer[1024];
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(8080);
    int clientAddrSize = sizeof(clientAddr);
    sendto(udpSocket, "Hello, UDP Server!", 18, 0, (SOCKADDR*)&clientAddr, clientAddrSize);
    while (true) {
        int bytesReceived = recvfrom(udpSocket, buffer, sizeof(buffer) - 1, 0, (SOCKADDR*)&clientAddr, &clientAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            //break;
            
            continue;
        }
        buffer[bytesReceived] = '\0';
        // Process the received data (for example, print it)
        std::cout << "Received: " << buffer << std::endl;
    }

    closesocket(udpSocket);
    WSACleanup();
    return 0;
}
