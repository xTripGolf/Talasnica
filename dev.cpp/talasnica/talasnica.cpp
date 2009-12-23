#include "talasnica.h"

using namespace std;

	Talasnica::Type::PacketFilter Talasnica::PacketFilter(int i) {
		switch (i)
		{
			case 0:
				return Talasnica::Type::BUY;
			case 1:
				return Talasnica::Type::SELL;
			case 2:
				return Talasnica::Type::BUYLIMIT;
			case 3:
				return Talasnica::Type::SELLLIMIT;
			case 4:
				return Talasnica::Type::BUYSTOP;
			case 5:
				return Talasnica::Type::SELLSTOP;
			case 6:
				return Talasnica::Type::PROFITED;
			case 7:
				return Talasnica::Type::LOSSED;
			case 8:
				return Talasnica::Type::ALL_OPENED;
			case 9:
				return Talasnica::Type::PREMOC;
			default:
				throw Talasnica::Exception("Nelze pøevést int na PacketFilter");
		}
	}

	Talasnica::Type::Order Talasnica::OrderType(int i) {
		switch (i)
		{
			case 0:
				return Talasnica::Type::OP_BUY;
			case 1:
				return Talasnica::Type::OP_SELL;
			case 2:
				return Talasnica::Type::OP_BUYLIMIT;
			case 3:
				return Talasnica::Type::OP_SELLLIMIT;
			case 4:
				return Talasnica::Type::OP_BUYSTOP;
			case 5:
				return Talasnica::Type::OP_SELLSTOP;
			default:
				throw Talasnica::Exception("Nelze pøevést int na OrderType");
		}
	}