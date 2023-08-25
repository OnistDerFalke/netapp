#pragma once
#include <ctime>
#include <string>

//Taka klasa do przechowywania wiadomosci i awatara jako string z metodami zamiany na string i na odwrot
class SerializableChatMessage
{
public:
	std::string message;
	std::string avatar;

	SerializableChatMessage(std::string message, std::string avatar);
	std::string ToString();
	SerializableChatMessage FromString(std::string data);
};

