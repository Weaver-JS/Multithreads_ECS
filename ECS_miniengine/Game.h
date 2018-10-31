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

