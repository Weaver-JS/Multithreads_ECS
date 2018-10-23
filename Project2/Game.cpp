#include "Game.h"



Game::Game()
{
}


Game::~Game()
{

}


void PongGame::init(std::string gameName, ECS::World * world, InputHandler * inputHandler)
{
	this->gameName = std::move(gameName);
	this->inputHandler = inputHandler;
	this->world = world;
	
	this->world->createWorld();
	ECS::Entity * righ_paddle;
	ECS::Entity * left_paddle;
	ECS::Entity * ball;

	righ_paddle = this->world->create();
	left_paddle = this->world->create();
	ball = this->world->create();
}

void PongGame::update()
{

}

void PongGame::destroy()
{

}
