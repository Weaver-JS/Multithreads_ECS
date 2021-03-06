#include "InputHandler.h"



bool InputHandler::inputLoop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT) return true;
		else if (event.type == SDL_KEYDOWN) {
			for (auto input : commands)
			{
				if ( std::get<2>(input) != nullptr && std::get<1>(input) == event.key.keysym.sym) //  std::get<Command*>(commands[0])
					std::get<2>(input)->execute(nullptr);
			}
			
			
		}
		else if (event.type == SDL_KEYUP)
			keyup(event);
	}
	return false;
}

void InputHandler::dispatcher(std::vector<Command*>& command_queue)
{

}

void InputHandler::keydown(SDL_Event & event)
{
	
}

void InputHandler::keyup(SDL_Event & event)
{
	

	
}

bool InputHandler::is_held(int key)
{

	return false;
}

bool InputHandler::was_pressed(int key)
{
	return false;
}

InputHandler::InputHandler()
{
	numberOfInputs = 0;
}


InputHandler::~InputHandler()
{
	for (auto  c : commands)
	{
		delete std::get<2>(c);
	}
	commands.clear();
}

void InputHandler::addInput(int key, Command * command)
{
	commands.push_back(std::make_tuple(numberOfInputs,key,command));
	numberOfInputs++;
	
}

void InputHandler::bind(int key, Command * command)
{
	for (int i = 0; i < numberOfInputs; ++i)
	{
		
	}
}

bool InputHandler::generate_input_commands(std::vector<Command*>& command_queue)
{
	return true;
}
