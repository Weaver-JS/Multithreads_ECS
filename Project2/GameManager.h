#include "Game.h"
#include "SDL.h"
#include "ECS.h"
#include "ECS_Components.h"
#include "ECS_Systems.h"
#include <iostream>
#include <exception>
struct exception_GameManager : std::runtime_error
{
	exception_GameManager(std::string &e) : std::runtime_error(std::move(e).c_str())
	{

	}
};
#define FRAMES_PER_SECOND 120
class GameManager {

private:
	static GameManager* instance;
	Game* game;
	ECS::World * world;
	SDL_Window * window;
	SDL_Renderer *renderer;
	void initializeRenderSystem();
	bool active;
	float deltaTime;
	uint64_t lastTickTime;
	bool fpsCap;
	Uint32 fpsLimiter;
	
	
	GameManager();
	~GameManager();
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	static GameManager* getInstance();
	void execute();
	void pause();
	void changeGame(Game * g);
};
