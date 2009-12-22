#pragma once

#include <string>

namespace Talasnica
{
	class Exception
	{
	public:
		Exception(char * message);
		~Exception(void);
		std::string message;
	};	
}


