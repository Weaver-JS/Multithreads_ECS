#pragma once
#include <SDL.h>
#include "ECS.h"
#include <iostream>
#include <map>
#include <vector>
#define MAX_COMMAND_INDEX	10
enum InputType {
	ACTION,
	STATE,
	RANGE
};
enum Action
{
	EXECUTE = true,
	STOP = false
};

enum State {
	PRESSED = true,
	RELEASED = false
};
struct Command {
public:
	virtual ~Command(){}
	virtual void execute(ECS::Entity * ent) = 0;
	virtual InputType get_input_type() = 0;
	std::function<void()> function_to_execute ;
};
class InputHandler
{
private:
	
	std::vector<std::tuple<int,int, Command*>> commands;

	std::map <int,State> state_map;
	std::map<int,Action>action_map;
	
	void dispatcher(std::vector<Command*> & command_queue);

	void keydown(SDL_Event & event);
	void keyup(SDL_Event & event);

	bool is_held(int key);
	bool was_pressed(int key);
	int numberOfInputs;



public:
	InputHandler();
	~InputHandler();
	/*Adds a new Command to the key*/
	void addInput(int key, Command* command);
	/*Binds a different command to a existant key*/
	void bind(int key, Command* command);
	/*Removes a determined key-command*/
	void removeInput(int key, Command* command);
	bool generate_input_commands(std::vector<Command*> &command_queue);
	bool input_mapping();
};

