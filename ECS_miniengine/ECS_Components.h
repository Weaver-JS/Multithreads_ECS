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

