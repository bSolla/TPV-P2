#pragma once
#include "checkML.h"
#include "SDL.h" // Windows

class GameObject {
public:
// ---------------------- methods ------------------------------------------------------
	virtual ~GameObject () {};

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event &e) = 0;
};