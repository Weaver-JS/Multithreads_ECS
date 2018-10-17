#pragma once
class Game
{
friend class GameManager;
protected:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
public:
	Game();
	~Game();
};

