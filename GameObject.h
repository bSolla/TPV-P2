#pragma once
#include "checkML.h"

class GameObject {
public:
// ---------------------- methods ------------------------------------------------------
	virtual ~GameObject () {};

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents() = 0;
};