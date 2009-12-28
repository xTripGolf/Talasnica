#pragma once

#include "talasnica.h"
#include "Order.h"

namespace Talasnica {

	class Order;

	namespace Sort {
		class ByOpenPrice {
			public:
				bool operator()(Talasnica::Order * o1, Talasnica::Order * o2);
		};
	}
}
