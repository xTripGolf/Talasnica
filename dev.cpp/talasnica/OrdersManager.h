#pragma once

#include <map>
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
			std::map<Talasnica::Enum::PacketFilter, OrdersPacket> packet;
			std::map<Talasnica::Enum::PacketFilter, OrdersPacket> initialize_packet();
			static std::map<Talasnica::Enum::PacketFilter, const std::string> descriptions;
			static std::map<Talasnica::Enum::PacketFilter, const std::string> initialize_descriptions(void);
			static std::map<Talasnica::Enum::PacketFilter, const std::string> names;
 			static std::map<Talasnica::Enum::PacketFilter, const std::string> initialize_names(void);
		public:
      OrdersManager(void);
			~OrdersManager(void);
      void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(Talasnica::Enum::PacketFilter);
			double volume(void);
			double volume(Talasnica::Enum::PacketFilter);
			double profit(void);
			double profit(Talasnica::Enum::PacketFilter);
			double swap(void);
			double swap(Talasnica::Enum::PacketFilter);
			double totalProfit(void);
			double totalProfit(Talasnica::Enum::PacketFilter);
			double averageOpenPrice(void);
			double averageOpenPrice(Talasnica::Enum::PacketFilter);
			int getTicket(Talasnica::Enum::PacketFilter, unsigned int index);
			static std::string getPacketName(Talasnica::Enum::PacketFilter);
			static std::string getPacketDescription(Talasnica::Enum::PacketFilter);
			friend std::ostream& operator<<(std::ostream &os, Talasnica::OrdersManager &ordersManager);
  };
}