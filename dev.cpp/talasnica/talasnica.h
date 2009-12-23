#pragma once

#include <string>
#include <iostream>
#include <map>
//#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

#include "Exception.h"

namespace Talasnica
{
	namespace Type
	{
		enum Order {OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP};
		enum PacketFilter {BUY, SELL, BUYLIMIT, SELLLIMIT, BUYSTOP, SELLSTOP, PROFITED, LOSSED, ALL_OPENED, PREMOC};

		PacketFilter operator++(const PacketFilter& c, int);
	}
		Talasnica::Type::PacketFilter PacketFilter(int i);
		Talasnica::Type::Order OrderType(int i);

		
}