#include "Exception.h"

using namespace std;

Talasnica::Exception::EnumOverFlow::EnumOverFlow(char * message)
{
	this->message = string(message);
}

Talasnica::Exception::EnumOverFlow::~EnumOverFlow(void)
{
}

std::ostream& Talasnica::Exception::operator<<(::std::ostream &os, const Talasnica::Exception::Exception &e)
{
	os << "ERROR: " << e.message << endl;
	return os;
}


