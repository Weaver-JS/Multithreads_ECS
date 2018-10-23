#include "GameManager.h"
GameManager* GameManager::instance = 0;

void GameManager::initializeRenderSystem()
{
	SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("ECS_VIOD Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_MINIMIZED | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	GameManager::instance->world = ECS::World::createWorld();
	ECS::Entity * manolo = GameManager::instance->world->create();
	manolo->assign<VIOD_ENTITY>(rand() % 100, rand() % 100).get().direction = Vector2(rand() % 10, rand() % 10);
	manolo->assign<RENDER_COMPONENT>(SDL_CreateTexture(renderer, 32, SDL_TextureAccess::SDL_TEXTUREACCESS_STATIC,
		100, 100));
	GameManager::instance->world->registerSystem(new RenderSystem(window,renderer));
	GameManager::instance->world->registerSystem(new moveSystem());
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
	GameManager::getInstance()->changeGame(game);
}

GameManager::GameManager()
{
	active = true;
}

GameManager::~GameManager()
{
	if (instance != nullptr) {
		delete instance;
	}
	if (game != nullptr)
		delete game;
	world->destroyWorld();
	
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
		//do {
			if (game != nullptr && active)
			{
				Uint32 startTime = SDL_GetTicks();
				deltaTime = ((SDL_GetPerformanceCounter() - lastTickTime) * 1000 / (double)SDL_GetPerformanceFrequency());
				inputHandler->inputLoop();
				game->update();
				world->tick(deltaTime);
				lastTickTime = SDL_GetPerformanceCounter();
				fpsLimiter = SDL_GetTicks() - startTime;
				
				if (fpsCap && fpsLimiter < 1000.0f / FRAMES_PER_SECOND)
				{
					SDL_Delay((1000.0f / FRAMES_PER_SECOND) - fpsLimiter);
					
				}
				fpsLimiter = 0.0f;
				
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
