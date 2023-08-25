#pragma once
#include <ctime>

//Analogiczna klasa do SCM ale zmienne przechowywane w normalnych typach, nie stringach
class ChatMessage
{
public:
	ChatMessage(CString message, CImage avatar);
	CString message;
	CImage avatar;
};

