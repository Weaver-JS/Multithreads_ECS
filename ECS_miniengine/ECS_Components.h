#pragma once
#include "ECS.h"
#include "SDL.h"
#include "glm\common.hpp"
struct Vector2 {

	Vector2(int x, int y) : x(x), y(y) {}
	Vector2() {}
	int x;
	int y;
public:
	int getX() { return x; }
	int getY() { return y; }
};

struct RENDER_COMPONENT
{
	ECS_DECLARE_TYPE
	RENDER_COMPONENT(SDL_Texture * texture) {
	this->texture = texture;
	};

	SDL_Texture * texture;
};

struct VIOD_ENTITY {
	ECS_DECLARE_TYPE
	VIOD_ENTITY(int x, int y) : position(x, y) { direction.x = 0; direction.y = 0; }
	VIOD_ENTITY() {}
	Vector2 position;
	Vector2 direction;

};

struct Pong_transform {
	ECS_DECLARE_TYPE
	Pong_transform(glm::vec2 & pos, glm::vec2 & dir, float vel) {
		position = std::move(pos); direction = std::move(dir); velocity = vel;
	}
	glm::vec2 position;
	glm::vec2 direction;
	float velocity;
};

struct Pong_Render_Component {
	ECS_DECLARE_TYPE
	Pong_Render_Component(float width, float height)
	{
		rect.w = width;
		rect.h = height;
	}
	SDL_Rect rect;
};

struct Pong_AI_Component
{
	ECS_DECLARE_TYPE
		glm::vec2 p;
};

struct Pong_Rectangle_Collider {
	ECS_DECLARE_TYPE
	glm::vec2 * position;
	float width, height;
	Pong_Rectangle_Collider(glm::vec2 & transformPosition , float width, float height) {
		position = &transformPosition;
		this->width = width;
		this->height = height;
	}
};

struct Pong_Circle_Collider {
	ECS_DECLARE_TYPE
	glm::vec2 * position;
	float radius;
	Pong_Circle_Collider(glm::vec2 & transformPosition, float radius)
	{
		position = &transformPosition;
		this->radius = radius;
	}
};