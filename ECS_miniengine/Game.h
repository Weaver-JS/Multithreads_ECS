#pragma once
#include "SDL.h"
#include "ECS.h"
#include "ECS_Components.h"
#include "ECS_Systems.h"
#include "InputHandler.h"
#include "ManagerConstants.h"


/*
Clase padre de todos los Juegos. Para crear una clase que herede
de juego y sobrescriba sus metodos virtuales.
*/
class Game
{
	
friend class GameManager;
protected:
	virtual void init(std::string gameName, ECS::World * world, InputHandler * inputHandler) = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
	std::string gameName;
	InputHandler* inputHandler;
	ECS::World * world;
	bool quit;
public:
	Game();
	~Game();
};

/*
 Creamos una nueva clase que hereda de Game.
*/
struct pong_input : Command {
	ECS::Entity * right_paddle;
	virtual ~pong_input() override {}
	virtual void execute(ECS::Entity * ent) override {
		function_to_execute();
	};
	virtual InputType get_input_type() override {
		return InputType::ACTION;
	};
};

class PongGame : public Game {
private:
	ECS::Entity * right_paddle;

public:
	PongGame() :  Game(){}
	void init(std::string gameName, ECS::World * world, InputHandler * inputHandler) override;
	void update() override;
	void destroy() override;
	void input();

	

};
