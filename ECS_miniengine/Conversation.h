#pragma once
#include "Client.h"
#include "SdlWindow.h"
#include <cstdlib>
class Conversation
{
private:
	Client * cl_1;
	Client * cl_2;
	SdlWindow * window;
	float timeBetweenMessages;
public:
	Conversation(Client cl_1, Client cl2, SdlWindow window);
	~Conversation();

	void startConversation();
	void updateConversation();
};

