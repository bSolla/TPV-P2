using namespace std;

#include <string>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>

class ArkanoidError : public logic_error
{
public:
	ArkanoidError();
};

