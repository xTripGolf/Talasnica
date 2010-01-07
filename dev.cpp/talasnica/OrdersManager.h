#pragma once

#include <map>
#include "talasnica.h"
#include "type.h"

namespace Talasnica
{

	class Order;
	class OrdersPacket;

	class OrdersManager
	{
		private:
			//
			std::map<int,Order> ordersPool;
			std::map<Talasnica::Type::PacketFilter, OrdersPacket> packet;
			std::map<Talasnica::Type::PacketFilter, OrdersPacket> initialize_packet();
			//static std::map<Talasnica::Type::PacketFilter, const std::string> descriptions;
			//static std::map<Talasnica::Type::PacketFilter, const std::string> initialize_descriptions(void);
			//static std::map<Talasnica::Type::PacketFilter, const std::string> names;
 			//static std::map<Talasnica::Type::PacketFilter, const std::string> initialize_names(void);
		public:
      OrdersManager(void);
			~OrdersManager(void);
      void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(Talasnica::Type::PacketFilter);
			double volume(void);
			double volume(Talasnica::Type::PacketFilter);
			double profit(void);
			double profit(Talasnica::Type::PacketFilter);
			double swap(void);
			double swap(Talasnica::Type::PacketFilter);
			double totalProfit(void);
			double totalProfit(Talasnica::Type::PacketFilter);
			double averageOpenPrice(void);
			double averageOpenPrice(Talasnica::Type::PacketFilter);
			int getTicket(Talasnica::Type::PacketFilter, unsigned int index);
			//static std::string getPacketName(Talasnica::Type::PacketFilter);
			//static std::string getPacketDescription(Talasnica::Type::PacketFilter);
			friend std::ostream& operator<<(std::ostream &os, Talasnica::OrdersManager &ordersManager);
  };
}