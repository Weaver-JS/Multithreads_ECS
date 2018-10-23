#pragma once
#include "SDL.h"
#include "ECS.h"
#include "ECS_Components.h"
#include "ECS_Systems.h"
#include "InputHandler.h"



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
public:
	Game();
	~Game();
};

/*
 Creamos una nueva clase que hereda de Game.
*/

class PongGame : public Game {
	
struct GameData {
	const float RACKET_WIDTH = 14, RACKET_HEIGHT = 70;
	const float BALL_WIDTH = 15, BALL_HEIGHT = 15;
};
private:
	
	
public:
	PongGame() :  Game(){}
	void init(std::string gameName, ECS::World * world, InputHandler * inputHandler) override;
	void update() override;
	void destroy() override;

};
