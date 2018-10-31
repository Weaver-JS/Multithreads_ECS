#include "GameManager.h"
GameManager* GameManager::instance = 0;

void GameManager::initializeRenderSystem()
{
	SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("ECS_VIOD Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_MINIMIZED | SDL_WINDOW_OPENGL);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	GameManager::instance->world = ECS::World::createWorld();
	GameManager::instance->world->registerSystem(new RenderSystem(window, renderer));

	deltaTime = 0.0f;
	lastTickTime = 0.0f;
	fpsLimiter = 0.0f;
	fpsCap = true;
	std::vector<Command*> cmdVector;
	default_input * myInput = new default_input();
	myInput->function_to_execute = []() {GameManager::getInstance()->pause(); GameManager::getInstance()->quit = true; };
	cmdVector.push_back(myInput);
	inputHandler = new InputHandler();
	inputHandler->addInput(SDLK_ESCAPE, cmdVector[0]);

	Game * game = new PongGame();
	game->init("Pong Game" ,world, inputHandler);
	GameManager::getInstance()->changeGame(game);
}

GameManager::GameManager()
{
	active = true;
}

GameManager::~GameManager()
{
	
	if (game != nullptr)
		delete game;

	delete inputHandler;

	world->destroyWorld();

	SDL_DestroyWindow(window);
	SDL_Quit();
	
}

GameManager * GameManager::getInstance()
{
	if (instance == 0)
	{
		instance = new GameManager();
		GameManager::instance->initializeRenderSystem();
	}
	return instance;
	
}

ECS::World * GameManager::getWorld()
{
	return world;
}

InputHandler * GameManager::getInputHandler()
{
	return inputHandler;
}

SDL_Window * GameManager::getWindow()
{
	return window;
}

SDL_Renderer * GameManager::getRenderer()
{
	return renderer;
}

float GameManager::getDeltaTime()
{
	return deltaTime;
}

void GameManager::execute()
{
	try {
	
			if (game != nullptr && !game->quit)
			{
				Uint32 startTime = SDL_GetTicks();
				deltaTime =  startTime - lastTickTime;

				game->update();
				world->tick(deltaTime * 0.1f);

				fpsLimiter = SDL_GetTicks() - startTime;
				
				if (fpsCap && fpsLimiter < 1000.0f / FRAMES_PER_SECOND)
				{
					SDL_Delay((1000.0f / FRAMES_PER_SECOND) - fpsLimiter);
					
				}
				fpsLimiter = 0.0f;
				lastTickTime = startTime;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255.0f);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
				inputHandler->inputLoop();
			}
			
	}
	catch (exception_GameManager &e)
	{
		std::cout << e.what() << std::endl;
	}
}



void GameManager::pause()
{
	active = false;
}

void GameManager::changeGame(Game * g)
{
	if (game != nullptr)
	{
		pause();
		delete game;

		
	}
	game = g;
}

void GameManager::destroy()
{
	delete GameManager::instance;
}
