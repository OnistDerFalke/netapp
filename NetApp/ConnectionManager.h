#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "SerializableChatMessage.h"
#include <vector>
#include "ChatMessage.h"
#include "MainFrm.h"

#pragma comment(lib, "ws2_32.lib")

class CMainFrame;

class ConnectionManager
{
public:
    ConnectionManager();
    ~ConnectionManager();
    void SendMsg(const std::string message);
    void ListenForMessages(std::vector<ChatMessage>& messages, CRect& editRect, CMainFrame* frame);
private:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
};

