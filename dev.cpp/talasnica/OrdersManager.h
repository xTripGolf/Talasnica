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
			std::map<Type::PacketFilter, OrdersPacket> packet;
			std::map<Type::PacketFilter, OrdersPacket> initialize_packet();
			static std::map<Type::PacketFilter, const std::string> descriptions;
			static std::map<Type::PacketFilter, const std::string> initialize_descriptions(void);
			static std::map<Type::PacketFilter, const std::string> names;
 			static std::map<Type::PacketFilter, const std::string> initialize_names(void);
		public:
      OrdersManager(void);
			~OrdersManager(void);
      void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(Type::PacketFilter type);
			double volume(void);
			double volume(Type::PacketFilter type);
			double profit(void);
			double profit(Type::PacketFilter type);
			double swap(void);
			double swap(Type::PacketFilter type);
			double totalProfit(void);
			double totalProfit(Type::PacketFilter type);
			double averageOpenPrice(void);
			double averageOpenPrice(Type::PacketFilter type);
			int getTicket(Type::PacketFilter type, unsigned int index);
			std::string getPacketName(Type::PacketFilter type);
			std::string getPacketDescription(Type::PacketFilter type);
		friend std::ostream& operator<<(std::ostream &os, OrdersManager &objekt);
  };

}