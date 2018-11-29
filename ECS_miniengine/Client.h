#pragma once
#include <string>
#include <vector>
#include <time.h>
class Client
{
private:
	std::string name;
	std::vector<std::string> messages;
	unsigned int id;
public:
	Client(std::string n);
	~Client();
	void setMessagesVector(std::vector<std::string> msg);
	std::vector<std::string> getMessages();
	unsigned int getUserId();
	void setUserId(unsigned int id);

	const std::string getName();
};

