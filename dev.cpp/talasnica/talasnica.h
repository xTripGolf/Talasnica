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


	/*namespace Enum
	{
		enum Order {OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP};
		enum PacketFilter {BUY, SELL, BUYLIMIT, SELLLIMIT, BUYSTOP, SELLSTOP, PROFITED, LOSSED, ALL_OPENED, PREMOC};

	}*/

	//Talasnica::Type::PacketFilter PacketFilterEnum(int i);
	//Talasnica::Type::Order OrderEnum(int i);
	
}

//Talasnica::Type::PacketFilter operator++(Talasnica::Type::PacketFilter& c, int);
