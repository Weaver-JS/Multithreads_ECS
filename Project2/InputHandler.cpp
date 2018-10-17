#include "InputHandler.h"



bool InputHandler::input_mapping()
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
	/*std::map<int, Command*>::iterator iter;
	for (iter = commands.begin(); iter != commands.end(); iter++) {
		if (is_held(iter->first) && iter->second->get_input_type() == STATE)
			command_queue.push_back(iter->second);
		else if (was_pressed(iter->first) && iter->second->get_input_type() == ACTION)
			command_queue.push_back(iter->second);
	}*/
}

void InputHandler::keydown(SDL_Event & event)
{
	if (state_map[event.key.keysym.sym] == RELEASED)
		action_map[event.key.keysym.sym] = EXECUTE;
	state_map[event.key.keysym.sym] = PRESSED;
}

void InputHandler::keyup(SDL_Event & event)
{
	
	state_map[event.key.keysym.sym] = RELEASED;
	
}

bool InputHandler::is_held(int key)
{
	return  state_map[key];

}

bool InputHandler::was_pressed(int key)
{
	return action_map[key];
}

InputHandler::InputHandler()
{
	numberOfInputs = 0;
}


InputHandler::~InputHandler()
{
	/*std::map<int, Command*>::iterator iter;
	for (iter = commands.begin(); iter != commands.end(); iter++)
		delete iter->second;*/
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
		/*if (command == std::get<2>(commands[i]))
		{
			//commands[i] = 
		}*/
	}
}

bool InputHandler::generate_input_commands(std::vector<Command*>& command_queue)
{
	bool exit = input_mapping();
	if (exit) return true;
	else {
		dispatcher(command_queue);
		action_map.clear();
	}
	return false;
}
