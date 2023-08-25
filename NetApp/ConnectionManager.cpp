#include "pch.h"
#include "ConnectionManager.h"


ConnectionManager::ConnectionManager()
{
    //Konfiguracja polaczenia z serwerem
     if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
     }

     clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
     if (clientSocket == INVALID_SOCKET) {
         WSACleanup();
     }

     serverAddr.sin_family = AF_INET;
     serverAddr.sin_port = htons(12345);
     inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
}

ConnectionManager::~ConnectionManager()
{
    closesocket(clientSocket);
    WSACleanup();
}

void ConnectionManager::SendMsg(const std::string message)
{
    //Wysylanie wiadomosci serwera (zawiera zakodowany msg i avatar jako ciag znakow)
    sendto(clientSocket, message.c_str(), strlen(message.c_str()), 0, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
}

void ConnectionManager::ListenForMessages(std::vector<ChatMessage>& messages, CRect& editRect, CMainFrame* frame)
{
    //Nasluchiwanie w petli na nadchodzace wiadomosci, niestety jeszcze nie do konca dziala tak jak chcialem
    char buffer[1024];
    int serverAddrLen = sizeof(serverAddr);
    while (true) {
        int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&serverAddr), &serverAddrLen);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            SerializableChatMessage decoded("", "");
            decoded = decoded.FromString(buffer);
            messages.emplace_back(static_cast<CString>(decoded.message.c_str()), CImage());
            frame->UpdateMessagesWindow(editRect);
        }
    }
}

