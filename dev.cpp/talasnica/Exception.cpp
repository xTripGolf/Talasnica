#include "Exception.h"

using namespace std;

namespace Talasnica {

	Exception::Exception(char * message)
	{
		//Exception::Exception(string(message));
		this->message = string(message);
	}

	Exception::~Exception(void)
	{
	}

}

