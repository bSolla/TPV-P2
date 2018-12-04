#ifndef ARKANOIDERROR_H
#define ARKANOIDERROR_H

using namespace std;

#include <string>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>

class ArkanoidError : public logic_error {
public:
	ArkanoidError (const string& what_arg) : logic_error(what_arg) {}

	// gives info about the type of error
	virtual const char* what () const noexcept {
		return logic_error::what ();
	}
};

#endif // !ARKANOIDERROR_H