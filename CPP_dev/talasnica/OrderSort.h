#pragma once

#include <algorithm>

namespace Talasnica
{
	namespace Sort {
		class ByOpenPrice {
			public:
				bool operator()(Talasnica::Order * o1, Talasnica::Order * o2);
		};
	}
}
