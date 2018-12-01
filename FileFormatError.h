#pragma once

#include "ArkanoidError.h"

const string WRONG_COLOR = "wrong or impossible color code in the file";
const string WRONG_MAP_SIZE = "wrong or inconsistent map size";
const string WRONG_TYPE = "wrong type in the file input values";

class FileFormatError : public ArkanoidError {
public:
	FileFormatError(const string& errorType) : ArkanoidError("File format error: " + errorType + "\n") {}
};

