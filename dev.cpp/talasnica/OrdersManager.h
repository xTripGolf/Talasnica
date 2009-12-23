#pragma once
#include <string>
#include <iostream>
#include <map>
//#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

#include "Exception.h"
#include "talasnica.h"

namespace Talasnica
{

	class Order;
	class OrdersPacket;

	class OrdersManager
	{
		private:
			//
			std::map<int,Order> ordersPool;
			std::map<PacketFilter, OrdersPacket> packet;
			std::map<PacketFilter, OrdersPacket> initialize_packet();
			static std::map<PacketFilter, const std::string> descriptions;
			static std::map<PacketFilter, const std::string> initialize_descriptions(void);
			static std::map<PacketFilter, const std::string> names;
 			static std::map<PacketFilter, const std::string> initialize_names(void);
		public:
      OrdersManager(void);
			~OrdersManager(void);
      void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(PacketFilter type);
			double volume(void);
			double volume(PacketFilter type);
			double profit(void);
			double profit(PacketFilter type);
			double swap(void);
			double swap(PacketFilter type);
			double totalProfit(void);
			double totalProfit(PacketFilter type);
			double averageOpenPrice(void);
			double averageOpenPrice(PacketFilter type);
			int getTicket(PacketFilter type, unsigned int index);
			std::string getPacketName(PacketFilter type);
			std::string getPacketDescription(PacketFilter type);
		friend std::ostream& operator<<(std::ostream &os, OrdersManager &objekt);
  };

}