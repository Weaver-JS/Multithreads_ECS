#include <iostream>
#include "SDL.h"
#include "SDL_video.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include <SDL_keyboard.h>
#include "SdlWindow.h"
#include "ThreadPool.h"
#include "ThreadManager.h"
#include "ConversationManager.h"
#ifdef  main
#undef main
#endif //  main



TTF_Font * font;
bool init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		TTF_Init();
		font = TTF_OpenFont("arial.ttf", 500);
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		
	}

	return success;
}

void close()
{
	

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}
#define NUM_MESSAGES 4;



bool quit = false;


void createConversations(ConversationManager * cManager)
{
	while (!quit)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(TIMEBETWEENCONVERSATIONS));
		if (cManager->getClientSize() < MAX_CLIENTS)
		{
			Client  cl1(userNames[rand() % userNames.size()]);
			cl1.setMessagesVector(messagesList[rand() % messagesList.size()]);
			cManager->setNewClient(cl1);
		}
	}
}

int main()
{

	init();
	ConversationManager * cManager = new ConversationManager(font);
	ThreadManager::getInstance()->getThreadPool()->enqueue(createConversations, cManager);
	
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			cManager->handleEvents(e);
			
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}
		}
		cManager->updateWindows();
	
	}
	close();
	delete cManager;
}








