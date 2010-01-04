#include "Exception.h"

using namespace std;

Talasnica::Exception::EnumOverFlow::EnumOverFlow(char * message)
{
	this->message = string(message);
}

Talasnica::Exception::EnumOverFlow::~EnumOverFlow(void)
{
}



