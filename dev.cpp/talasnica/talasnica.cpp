#include "talasnica.h"

using namespace std;

	/*Talasnica::Type::PacketFilter operator++(Talasnica::Type::PacketFilter& c, int) {
		cout << "PacketFilterEnum operator++(const PacketFilterEnum& c) with " << c << endl;
		if(c >= Talasnica::Enum::PREMOC) {
			throw Talasnica::Exception::EnumOverFlow("PacketFilterEnum se dostává mimo povolený rozsah.");
		}
		int t = (int)c;
		t++;
		c = (Talasnica::Type::PacketFilter)t; 
		return c;
	}*/

	/*Talasnica::Type::PacketFilter Talasnica::PacketFilterEnum(int i) {
		switch (i)
		{
			case 0:
				return Talasnica::Enum::BUY;
			case 1:
				return Talasnica::Enum::SELL;
			case 2:
				return Talasnica::Enum::BUYLIMIT;
			case 3:
				return Talasnica::Enum::SELLLIMIT;
			case 4:
				return Talasnica::Enum::BUYSTOP;
			case 5:
				return Talasnica::Enum::SELLSTOP;
			case 6:
				return Talasnica::Enum::PROFITED;
			case 7:
				return Talasnica::Enum::LOSSED;
			case 8:
				return Talasnica::Enum::ALL_OPENED;
			case 9:
				return Talasnica::Enum::PREMOC;
			default:
				throw Talasnica::Exception::EnumOverFlow("Nelze pøevést int na PacketFilterEnum");
		}
	}

	Talasnica::Type::Order Talasnica::OrderEnum(int i) {
		switch (i)
		{
			case 0:
				return Talasnica::Enum::OP_BUY;
			case 1:
				return Talasnica::Enum::OP_SELL;
			case 2:
				return Talasnica::Enum::OP_BUYLIMIT;
			case 3:
				return Talasnica::Enum::OP_SELLLIMIT;
			case 4:
				return Talasnica::Enum::OP_BUYSTOP;
			case 5:
				return Talasnica::Enum::OP_SELLSTOP;
			default:
				throw Talasnica::Exception::EnumOverFlow("Nelze pøevést int na OrderEnum");
		}
	}*/
