#pragma once
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FRAMES_PER_SECOND 120

#define THREADSNUMBERS 7
#define MAX_CLIENTS 20

#define TIMEBETWEENCONVERSATIONS 1000

const std::vector<std::vector<std::string>> messagesList{
   std::vector<std::string>{"Hello","How Are you", "Fine", "random1" "Bye"},
   std::vector<std::string>{"No","No", "No", "No" "Bye"},
   std::vector<std::string>{"Yes","Yes", "Yes", "Yes" "Bye"},
   std::vector<std::string>{"Bye","Bye", "Bye", "Bye" "Bye"}
};

const std::vector<std::string> userNames
{
	"Li ming",
	"Zeratul",
	"Arthas",
	"Sonya",
	"Gazlowe"
};