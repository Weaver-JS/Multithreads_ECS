#include "Game.h"



Game::Game()
{
}


Game::~Game()
{

}

const float RACKET_WIDTH = 14, RACKET_HEIGHT = 70;
const float BALL_WIDTH = 15, BALL_HEIGHT = 15;
const float RIGHT_PADDLE_POSITION_X = RACKET_WIDTH , RIGHT_PADDLE_POSITION_Y = 70.0f;
const float LEFT_PADDLE_POSITION_X = WINDOW_WIDTH - (RACKET_WIDTH *2.0f ), LEFT_PADDLE_POSITION_Y = 70.0f;

void PongGame::input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_w)
			{
				right_paddle->get<Pong_transform>().get().direction.y = -1;
			}

			if (event.key.keysym.sym == SDLK_s)
			{
				right_paddle->get<Pong_transform>().get().direction.y = 1;
			}

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)
			{
				right_paddle->get<Pong_transform>().get().direction.y = 0.0f;
			}

	
		}
	
	}


}
void PongGame::init(std::string gameName, ECS::World * world, InputHandler * inputHandler)
{
	this->gameName = std::move(gameName);
	this->inputHandler = inputHandler;
	this->world = world;
	
	this->world->createWorld();
	right_paddle = world->create();
	ECS::Entity * left_paddle = world->create();
	ECS::Entity * ball = world->create();

	
	right_paddle->assign<Pong_transform>(glm::vec2(RIGHT_PADDLE_POSITION_X, RIGHT_PADDLE_POSITION_Y), glm::vec2(0.0f), 3.0f);
	right_paddle->assign<Pong_Render_Component>(RACKET_WIDTH, RACKET_HEIGHT);
	right_paddle->assign<Pong_Rectangle_Collider>(right_paddle->get<Pong_transform>().get().position, RACKET_WIDTH, RACKET_HEIGHT);
	
	left_paddle->assign<Pong_transform>(glm::vec2(LEFT_PADDLE_POSITION_X, LEFT_PADDLE_POSITION_Y), glm::vec2(0.0f), 3.0f);
	left_paddle->assign<Pong_Render_Component>(RACKET_WIDTH, RACKET_HEIGHT);
	left_paddle->assign<Pong_Rectangle_Collider>(left_paddle->get<Pong_transform>().get().position, RACKET_WIDTH, RACKET_HEIGHT);
	left_paddle->assign<Pong_AI_Component>();

	ball->assign<Pong_transform>(glm::vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), glm::vec2(0.5f,-0.5f),5.0f);
	ball->assign<Pong_Render_Component>(BALL_WIDTH, BALL_HEIGHT);
	ball->assign<Pong_Circle_Collider>(ball->get<Pong_transform>().get().position, BALL_WIDTH);

	
	
	world->registerSystem(new moveSystem());
	world->registerSystem(new collisionSystem());
	world->registerSystem(new AISystem());
	
}

void PongGame::update()
{
	input();
}

void PongGame::destroy()
{

}
