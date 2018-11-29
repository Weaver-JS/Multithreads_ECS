#include "ConversationManager.h"



ConversationManager::ConversationManager(TTF_Font * font)
{
	this->font = font;
	windows[0].init();
}


ConversationManager::~ConversationManager()
{
	for (int i = 0; i < MAX_WINDOWS; ++i)
	{
		windows[i].free();
	}
}

void ConversationManager::setNewConversation(Conversation c)
{
	cvsVector.push_back(c);
}

void ConversationManager::setNewClient(Client c)
{
	
	clientList.push_back(c);
	std::cout << "New Client waiting " << c.getName() <<std::endl;
}

void ConversationManager::updateWindows()
{
	for (int i = 0; i < MAX_WINDOWS; ++i)
	{
		windows[i].render();
		std::vector<std::string>hi {"Hello","How Are you", "Fine", "random1" ,  "Bye"} ;
		if(clientList.size() > 0)
		windows[i].renderText(clientList[0].getMessages(), font); // Text & font
	}
}

void ConversationManager::handleEvents(SDL_Event & e)
{
	for (int i = 0; i < MAX_WINDOWS; ++i)
	{
		windows[i].handleEvent(e);
	}
}

unsigned int ConversationManager::getClientSize()
{
	return clientList.size();
}
