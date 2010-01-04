#pragma once

#include <string>

namespace Talasnica
{
	namespace Exception {
		class Exception {
			public:
				std::string message;
			friend ::std::ostream& operator<<(::std::ostream &os, const Talasnica::Exception::Exception &e);
		};

		class EnumOverFlow : public  Exception
		{
			public:
				EnumOverFlow(char * message);
				~EnumOverFlow(void);
		};
	}
}


