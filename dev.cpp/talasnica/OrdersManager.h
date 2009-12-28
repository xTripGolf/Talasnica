#pragma once

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
			int count(Talasnica::Enum::PacketFilter type);
			double volume(void);
			double volume(Talasnica::Enum::PacketFilter type);
			double profit(void);
			double profit(Talasnica::Enum::PacketFilter type);
			double swap(void);
			double swap(Talasnica::Enum::PacketFilter type);
			double totalProfit(void);
			double totalProfit(Talasnica::Enum::PacketFilter type);
			double averageOpenPrice(void);
			double averageOpenPrice(Talasnica::Enum::PacketFilter type);
			int getTicket(Talasnica::Enum::PacketFilter type, unsigned int index);
			std::string getPacketName(Talasnica::Enum::PacketFilter type);
			std::string getPacketDescription(Talasnica::Enum::PacketFilter type);
		friend std::ostream& operator<<(std::ostream &os, OrdersManager &objekt);
  };

}