#pragma once
#include <iostream>
#include "ECS_Systems.h"
#include "ManagerConstants.h"
#include "glm/geometric.hpp"

struct RenderSystem : public ECS::EntitySystem {

private:
	SDL_Window* window;
	SDL_Renderer * renderer;
public:
	RenderSystem(SDL_Window *window_,
		SDL_Renderer * renderer_)
	{
		window = window_;
		renderer =  renderer_;
	}

	virtual ~RenderSystem() {}
	void updateRender(ECS::Entity * ent, ECS::ComponentHandle<RENDER_COMPONENT> rectangle)
	{

	}

	virtual void tick(ECS::World* world, float delta)
	{
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255.0f);
		SDL_RenderClear(renderer);
		world->each<RENDER_COMPONENT>([&](ECS::Entity * ent, ECS::ComponentHandle<RENDER_COMPONENT> rectangle)
		{
			
				SDL_SetRenderTarget(renderer, rectangle.get().texture);
			
				SDL_SetRenderDrawColor(renderer, 255.0f, 255.0f, 255.0f, 255.0f);
		});



		SDL_RenderPresent(renderer);

		
	}
	void cleanRenderer() {

	}

};

struct moveSystem : public ECS::EntitySystem
{
public:
	moveSystem()
	{

	}
	virtual ~moveSystem() {}

	virtual void tick(ECS::World* world, float delta)
	{
		
	}
};
