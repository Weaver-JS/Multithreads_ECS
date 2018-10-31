#include <iostream>
#include "ECS.h"
#include "ECS_Components.h"
#include "ECS_Systems.h"
#include "SDL.h"
#include "SDL_video.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include <SDL_keyboard.h>
#include "GameManager.h"
#include "InputHandler.h"

#ifdef  main
#undef main
#endif //  main

int main()
{
	while (!GameManager::getInstance()->quit)
	{
		GameManager::getInstance()->execute();
	}

	GameManager::getInstance()->destroy();
}