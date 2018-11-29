#include "Conversation.h"





Conversation::Conversation(Client cl_1, Client cl2, SdlWindow  window)
{
	this->cl_1 = &cl_1;
	this->cl_2 = &cl2;
	this->window = &window;
	timeBetweenMessages = (rand() % 10) + 2;
	
}
void Conversation::startConversation()
{
	window->init();
}

void Conversation::updateConversation()
{

}

Conversation::~Conversation()
{
	delete cl_1;
	delete cl_2;
}
