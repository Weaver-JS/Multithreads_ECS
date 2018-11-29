#pragma once
#include "Conversation.h"
#include <iostream>
#define MAX_WINDOWS 8

class ConversationManager
{
private:
	std::vector<Conversation> cvsVector;
	SdlWindow windows[MAX_WINDOWS];
	std::vector<Client> clientList;
	TTF_Font * font;
public:
	ConversationManager(TTF_Font * font);
	~ConversationManager();

	void setNewConversation(Conversation c);
	void setNewClient(Client c);

	void updateWindows();
	void handleEvents(SDL_Event & e);
	unsigned int getClientSize();
	
};

