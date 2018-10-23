#include "Game.h"
#include "SDL.h"
#include "ECS.h"
#include "ECS_Components.h"
#include "ECS_Systems.h"
#include "InputHandler.h"
#include <iostream>
#include <exception>

struct default_input : Command {
	virtual ~default_input() override {}
	virtual void execute(ECS::Entity * ent) override {
		function_to_execute();
	};
	virtual InputType get_input_type() override {
		return InputType::ACTION;
	};

};
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
	SDL_Renderer * renderer;
	InputHandler * inputHandler;

	float deltaTime;
	uint64_t lastTickTime;
	bool active;
	bool fpsCap;
	Uint32 fpsLimiter;
	
	void initializeRenderSystem();
	GameManager();
	~GameManager();
	
public:
	bool quit = false;
	/*As GameManager is a Singleton we delete copy and reference operators*/
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	/*Getters*/
	static GameManager* getInstance();
	ECS::World * getWorld();
	InputHandler * getInputHandler();
	SDL_Window * getWindow();
	SDL_Renderer * getRenderer();
	float getDeltaTime();

	/*Methods*/
	void execute();
	void pause();
	void changeGame(Game * g);
};
