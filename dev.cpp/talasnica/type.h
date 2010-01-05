#pragma once

#include <map>
#include <string>
#include "talasnica.h"

namespace Talasnica
{

	/*class Order;
	class OrdersManager;
	class OrdersPacket;

	namespace Sort {
		class ByOpenPrice;
	}*/

	namespace Type {
		class Order {
			private:
				int	value;
				static std::map<const int, const std::string> initialize_names(void);
			public:
				Order(int);
				~Order(void);
				static const int BUY = 0;
				static const int SELL = 1;
				static const int BUYLIMIT = 2;
				static const int SELLLIMIT = 3;
				static const int BUYSTOP = 4;
				static const int SELLSTOP = 5;
				static std::map<const int, const std::string> names;
		};
	}
}

