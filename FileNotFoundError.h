#pragma once

#include "ArkanoidError.h"

class FileNotFoundError : public ArkanoidError {
public:
	FileNotFoundError (const string& fileName) : ArkanoidError ("File " + fileName + " could not be found\n") {}
};

