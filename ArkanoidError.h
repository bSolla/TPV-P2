#ifndef ARKANOIDERROR_H
#define ARKANOIDERROR_H

using namespace std;

#include <string>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>

class ArkanoidError : public logic_error {
private:
	string msg;

public:
	ArkanoidError (const string& what_arg) : logic_error(what_arg) {}
	ArkanoidError (const char* what_arg) : logic_error(what_arg) {}

	// gives info about the type of error
	virtual const char* what () const noexcept {
		return msg.c_str();
	}
};

#endif // !ARKANOIDERROR_H