#pragma once

namespace Talasnica
{
		enum OrderType {OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP};
		enum PacketFilter {BUY, SELL, BUYLIMIT, SELLLIMIT, BUYSTOP, SELLSTOP, PROFITED, LOSSED, ALL_OPENED, PREMOC};

		PacketFilter operator++(const PacketFilter& c, int);
}