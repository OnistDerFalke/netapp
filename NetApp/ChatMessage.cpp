#include "pch.h"
#include "ChatMessage.h"

ChatMessage::ChatMessage(CString message, std::time_t sendTime, CImage avatar, CString username, bool incoming) :
	message(message), sendTime(sendTime), avatar(avatar), username(username), incoming(incoming) {}