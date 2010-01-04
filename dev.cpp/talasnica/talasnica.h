#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>

//#include "../Logger/Logger.h"

#include "Exception.h"

namespace Talasnica
{

	class Order;
	class OrdersManager;
	class OrdersPacket;

	namespace Sort {
		class ByOpenPrice;
	}

	/*namespace Type {
		class Order {
		public:
			static const int OP_BUY = 1;
			static const int OP_SELL = 2;
			static const int OP_BUYLIMIT = 3;
			static const int OP_SELLLIMIT = 4;
			static const int OP_BUYSTOP = 5;
			static const int OP_SELLSTOP = 6;
		};
	}*/

	namespace Enum
	{
		enum Order {OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP};
		enum PacketFilter {BUY, SELL, BUYLIMIT, SELLLIMIT, BUYSTOP, SELLSTOP, PROFITED, LOSSED, ALL_OPENED, PREMOC};

	}

	Talasnica::Enum::PacketFilter PacketFilterEnum(int i);
	Talasnica::Enum::Order OrderEnum(int i);
	
}

Talasnica::Enum::PacketFilter operator++(Talasnica::Enum::PacketFilter& c, int);
