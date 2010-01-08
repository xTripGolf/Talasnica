#pragma once

#include <string>

namespace Talasnica
{
	namespace Exception {
		class Exception {
			protected:
				std::string message;
			public:
		friend std::ostream& operator<<(std::ostream &os, const Talasnica::Exception::Exception &e);
		};

		class TypeOverFlow : public  Exception
		{
			public:
				TypeOverFlow(char * message);
				~TypeOverFlow(void);
		};
	}
}


