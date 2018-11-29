#pragma once
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, strings, and string streams
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Total windows
const int TOTAL_WINDOWS = 7;

class SdlWindow
{
public:
	//Intializes internals
	SdlWindow();

	//Creates window
	bool init();

	//Handles window events
	void handleEvent(SDL_Event& e);

	//Focuses on window
	void focus();

	//Shows windows contents
	void render();

	//Deallocates internals
	void free();

	void renderText(std::vector<std::string> & v,TTF_Font * f);

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
	

private:
	//Window data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Color color;
	
	int mWindowID;

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};