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
	void updateRender(ECS::Entity * ent, ECS::ComponentHandle<Pong_Render_Component> rectangle)
	{

	}

	virtual void tick(ECS::World* world, float delta)
	{
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255.0f);
		SDL_RenderClear(renderer);
		world->each<Pong_Render_Component>([&](ECS::Entity * ent, ECS::ComponentHandle<Pong_Render_Component> rectangle)
		{
			if (ent->has<Pong_transform>())
			{
				rectangle.get().rect.x = ent->get<Pong_transform>().get().position.x; // +(rectangle.get().rect.w / 2.0f);
				rectangle.get().rect.y = ent->get<Pong_transform>().get().position.y;// +(rectangle.get().rect.h / 2.0f);
			}
			if (ent->has<Pong_Rectangle_Collider>())
			{
				SDL_SetRenderDrawColor(renderer, 0.0f, 255.0f, 0.0f, 255.0f);
				SDL_Rect tempRect;
				tempRect.x = ent->get<Pong_Rectangle_Collider>().get().position->x;
				tempRect.y = ent->get<Pong_Rectangle_Collider>().get().position->y;
				tempRect.w = ent->get<Pong_Rectangle_Collider>().get().width;
				tempRect.h = ent->get<Pong_Rectangle_Collider>().get().height;
				SDL_RenderFillRect(renderer, &tempRect);
			}
			SDL_SetRenderDrawColor(renderer, 255.0f, 255.0f, 255.0f, 255.0f);
			SDL_RenderFillRect(renderer, &rectangle.get().rect);
			

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
		world->each<Pong_transform>([&](ECS::Entity * ent, ECS::ComponentHandle<Pong_transform> postion)
		{
			postion->position.x += postion->direction.x * postion->velocity * delta;
			postion->position.y += postion->direction.y * postion->velocity * delta;

#ifdef _DEBUG
			
#endif
		});
	}
};
struct AISystem : public ECS::EntitySystem {
public:
	AISystem()
	{

	}
	virtual ~AISystem() {}

	virtual void tick(ECS::World* world, float delta)
	{
		world->each<Pong_AI_Component>([&](ECS::Entity * ent, ECS::ComponentHandle<Pong_AI_Component> postion){
			world->each<Pong_Circle_Collider>([&](ECS::Entity * entLol, ECS::ComponentHandle<Pong_Circle_Collider> postion)
			{
				if (ent->get<Pong_transform>().get().position.y > postion.get().position->y)
				{
					ent->get<Pong_transform>().get().direction.y = -1;
				}
				else {
					ent->get<Pong_transform>().get().direction.y = 1;
				}

			});

			
		});
	}
};

struct collisionSystem : public ECS::EntitySystem {	
	collisionSystem()
	{

	}
	virtual ~collisionSystem() {}
	bool detectCollisionBetweenBallRacket(Pong_Circle_Collider & circleCollider, Pong_Rectangle_Collider & rectCollider) { 
		float NearestX = glm::max(rectCollider.position->x,
			glm::min(circleCollider.position->x, rectCollider.position->x + rectCollider.width));
		float NearestY = glm::max(rectCollider.position->y,
			glm::min(circleCollider.position->y, rectCollider.position->y + rectCollider.height));
		float	DeltaX = circleCollider.position->x - NearestX;
		float	DeltaY = circleCollider.position->y - NearestY;
		return (DeltaX * DeltaX + DeltaY * DeltaY) < (circleCollider.radius * circleCollider.radius);
	 }


	void print(ECS::Entity * e)
	{}
	virtual void tick(ECS::World * world, float delta)
	{


		world->each<Pong_Circle_Collider>([&](ECS::Entity * ent, ECS::ComponentHandle<Pong_Circle_Collider> circleCollider)
		{
			if (ent->get<Pong_transform>().get().position.y <= 10 || ent->get< Pong_transform>().get().position.y >= WINDOW_HEIGHT- 10) {
				ent->get<Pong_transform>().get().direction.y *= -1;
			}
			if (ent->get<Pong_transform>().get().position.x <= 0.0f || ent->get<Pong_transform>().get().position.x >= WINDOW_WIDTH)
			{
				ent->get<Pong_transform>().get().position = glm::vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
				ent->get<Pong_transform>().get().direction *= -1;
			}
			world->each<Pong_Rectangle_Collider>([&](ECS::Entity * rect, ECS::ComponentHandle<Pong_Rectangle_Collider> rectCollider)
			{
				if (detectCollisionBetweenBallRacket(circleCollider.get(), rectCollider.get()))
				{
					ent->get<Pong_transform>().get().direction.x *= -1.0f;
					ent->get<Pong_transform>().get().position += ent->get<Pong_transform>().get().direction * ent->get<Pong_transform>().get().velocity;
				}
				rect->get<Pong_transform>().get().position.y  = glm::clamp(rect->get<Pong_transform>().get().position.y, 0.0f, (float)WINDOW_HEIGHT - 70.0f);
			});

			
		});
	}
};