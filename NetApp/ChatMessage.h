#pragma once
#include <ctime>

class ChatMessage
{
public:
	ChatMessage(CString message, std::time_t sendTime, CImage avatar, CString username, bool incoming);
	CString message;
	std::time_t sendTime;
	CImage avatar;
	CString username;
	bool incoming;
};

