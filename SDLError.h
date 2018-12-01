#pragma once

#include "ArkanoidError.h"

class SDLError : public ArkanoidError {
public:
	SDLError (const string& what_arg) : ArkanoidError (what_arg) {} // specific message is sent using SDL error in the appropiate modules
};

