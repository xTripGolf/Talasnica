#pragma once

#include <string>

namespace Talasnica
{
	namespace Exception {
		class EnumOverFlow
		{
			public:
				EnumOverFlow(char * message);
				~EnumOverFlow(void);
				std::string message;
		};
	}
}


