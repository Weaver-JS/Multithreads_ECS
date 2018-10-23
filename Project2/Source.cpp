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
bool quit = false;
void getInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{

		case SDL_KEYDOWN:
			quit = true;
			std::cout << "Key press detected\n" << std::endl;
			break;

		case SDL_KEYUP:
			//quit = true;
			
			break;

		default:
			break;
		}

	}
}

struct p : Command {
	void execute(ECS::Entity * ent){
		std::cout << " Funciona" << std::endl;
	}
	InputType get_input_type() {
		return InputType::ACTION;
	};
};

struct obj {
	int mainCount = 0;
	void sum1() {
		mainCount++;
	}
};
struct myCommand : Command {
	void execute(ECS::Entity * ent) {
		function_to_execute();//{std::cout<< "lol"<<std::endl};
	}
	InputType get_input_type() {
		return InputType::ACTION;
	};
	int myNumber = 0;
};


struct myGame : Game {
	void init() {};
	void update() {};
	void destroy() {};
};
int main()
{
	
	/*GameManager * gm = GameManager::getInstance();
	obj object;
	Command * cm = new myCommand();
	Command* closeCMD = new myCommand();
	std::vector<Command*> cmdVector(2);
	cmdVector[0] = cm;
	cmdVector[1] = closeCMD;
	int  nm = dynamic_cast<myCommand*>(cm)->myNumber;
	cm->function_to_execute = [&nm]() {std::cout << "printed" << std::endl; nm++; std::cout << nm << std::endl; };
	InputHandler inputhandler;
	inputhandler.addInput(SDLK_q, cmdVector[0]);
	closeCMD->function_to_execute = [&quit]() {quit = true;};
	inputhandler.addInput(SDLK_ESCAPE, cmdVector[1]);*/

	while (!GameManager::getInstance()->quit)
	{
		GameManager::getInstance()->execute();
	}

	/*Game * game = new myGame();
	GameManager::getInstance()->changeGame(game);

	while (!quit)
	{
		inputhandler.input_mapping();
		gm->execute();
	//	quit = inputHandler.generate_input_commands(command_queue);
		//inputHandler.input_mapping();
			
		
		//getInput();
	}*/
}