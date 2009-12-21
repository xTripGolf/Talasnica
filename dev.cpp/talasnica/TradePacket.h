#pragma once
#include <string>
#include <iostream>
#include <map>
//#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

#include "dataType.h"

namespace Talasnica
{

	class Order;
	class AverageOrder;

	class TradePacket
	{
		private:
			//
			std::map<int,Order> tradeList;
			std::map<OrdersGroup, AverageOrder> packet;
			std::map<OrdersGroup, AverageOrder> initialize_packet();
			/*static*/ std::map<OrdersGroup, const std::string> descriptions;
			/*static*/ std::map<OrdersGroup, const std::string> initialize_descriptions(void);
			public:
        TradePacket(void);
				~TradePacket(void);
        void add(Order&);
				void reset(void);
				int count();
		friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
  };

}