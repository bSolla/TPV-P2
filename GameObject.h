#pragma once
#include "checkML.h"

class GameObject {
public:
// ---------------------- methods ------------------------------------------------------
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void HandleEvents() = 0;
};