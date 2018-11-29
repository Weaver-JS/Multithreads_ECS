#include "Client.h"



Client::Client(std::string n)
{
	name = n;
	srand((unsigned)(time(0)));
}

unsigned int Client::getUserId()
{
	return id;
}

void Client::setUserId(unsigned int id)
{
	this->id = id;
}

const std::string Client::getName()
{
	return name;
}

Client::~Client()
{
}

void Client::setMessagesVector(std::vector<std::string> msg)
{
	
	for (int i = 0; i < msg.size(); ++i)
	{
		if (rand() % 5 == 1)
		{
			msg[i] = "ESCAPE";
		}
		msg[i].insert(0, name + ": ");
		
	}
	messages = msg;
}

std::vector<std::string> Client::getMessages()
{
	return messages;
}
