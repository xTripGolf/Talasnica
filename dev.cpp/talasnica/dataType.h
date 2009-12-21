#pragma once

namespace Talasnica
{
	enum OperationType {OP_BUY, OP_SELL, OP_BUYLIMIT, OP_SELLLIMIT, OP_BUYSTOP, OP_SELLSTOP};
	enum OrdersGroup {BUY, SELL, BUYLIMIT, SELLLIMIT, BUYSTOP, SELLSTOP, PROFITED, LOSSED, ALL_OPENED, PREMOC};

	OrdersGroup operator++(const OrdersGroup& c, int);
}