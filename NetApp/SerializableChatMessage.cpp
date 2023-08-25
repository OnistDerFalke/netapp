#include "pch.h"
#include "SerializableChatMessage.h"

SerializableChatMessage::SerializableChatMessage(std::string message, std::string avatar) :
	message(message), avatar(avatar) {}

std::string SerializableChatMessage::ToString()
{
    return message + "|" + avatar;
}

SerializableChatMessage SerializableChatMessage::FromString(std::string data)
{
    size_t delimiterPos = data.find("|");
    if (delimiterPos != std::string::npos) {
        std::string msg = data.substr(0, delimiterPos);
        std::string av = data.substr(delimiterPos + 1);
        return SerializableChatMessage(msg, av);
    }
    return SerializableChatMessage("", "");
}