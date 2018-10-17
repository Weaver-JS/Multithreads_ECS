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

void GameManager::execute()
{
	try {
		//do {
			if (game != nullptr && active)
			{
				Uint32 startTime = SDL_GetTicks();
				deltaTime = ((SDL_GetPerformanceCounter() - lastTickTime) * 1000 / (double)SDL_GetPerformanceFrequency());
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
