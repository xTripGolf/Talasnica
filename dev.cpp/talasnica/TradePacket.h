#pragma once
#include <string>
#include <iostream>
#include <map>
//#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

#include "Exception.h"
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
			static std::map<OrdersGroup, const std::string> descriptions;
			static std::map<OrdersGroup, const std::string> initialize_descriptions(void);
		public:
      TradePacket(void);
			~TradePacket(void);
      void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(OrdersGroup type);
			double volume(void);
			double volume(OrdersGroup type);
			double profit(void);
			double profit(OrdersGroup type);
			double swap(void);
			double swap(OrdersGroup type);
			double totalProfit(void);
			double totalProfit(OrdersGroup type);
			double averageOpenPrice(void);
			double averageOpenPrice(OrdersGroup type);
			int getTicket(OrdersGroup type, unsigned int index);
		friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
  };

}