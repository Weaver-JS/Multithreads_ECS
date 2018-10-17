#pragma once
#include <iostream>
#include "ECS_Systems.h"

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
	virtual void tick(ECS::World* world, float delta)
	{
		
		//SDL_RenderPresent(renderer);
		world->each<RENDER_COMPONENT>([&](ECS::Entity * ent, ECS::ComponentHandle<RENDER_COMPONENT> texture)
		{
			SDL_SetRenderTarget(renderer, texture.get().texture);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture.get().texture, NULL, NULL);
			SDL_SetRenderTarget(renderer, NULL);

		});

		
		SDL_RenderClear(renderer);
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
		world->each<VIOD_ENTITY>([&](ECS::Entity * ent, ECS::ComponentHandle<VIOD_ENTITY> postion)
		{
			postion->position.x += postion->direction.x;
			postion->position.y += postion->direction.y;
#ifdef _DEBUG
			std::cout << ent->get<VIOD_ENTITY>().get().position.x << " " << ent->get<VIOD_ENTITY>().get().position.y << std::endl;
#endif
		});
	}
};

