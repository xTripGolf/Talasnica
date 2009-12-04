#pragma once
#include "Order.h"
//#include <stack>
#include <map>
#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

using namespace std;

namespace Talasnica
{

	class TradePacket
	{
		private:
			//
			map<int,Order> zasobnik;
			public:
        TradePacket(void);
				~TradePacket(void);
        void add(Order order);
				void reset(void);
				int count(int type=0);
				string getInfo(void);
  };
}