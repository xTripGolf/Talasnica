#include "StdAfx.h"
#include "Exception.h"

using namespace std;

Talasnica::Exception::TypeOverFlow::TypeOverFlow(char * message)
{
	this->message = string(message);
}

Talasnica::Exception::TypeOverFlow::~TypeOverFlow(void)
{
}



