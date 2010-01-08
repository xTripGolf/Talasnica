#pragma once

#include "OrderPacket.h"

namespace Talasnica {

	class Order;

	class OrderManager
	{
		typedef std::map<int,Order> OrdersPoolMap;
		typedef std::map<Talasnica::Type::Packet, Talasnica::OrderPacket> PacketMap;
		private:
				OrdersPoolMap ordersPool;
				PacketMap packet;
				PacketMap initialize_packet();
		public:
			OrderManager(void);
			~OrderManager(void);
			void add(Order);
			void sort();
			void reset(void);
			int count(void);
			int count(Talasnica::Type::Packet);
			//double volume(void);
			double volume(Talasnica::Type::Packet);
			//double profit(void);
			double profit(Talasnica::Type::Packet);
			//double swap(void);
			double swap(Talasnica::Type::Packet);
			//double totalProfit(void);
			double totalProfit(Talasnica::Type::Packet);
			//double averageOpenPrice(void);
			double averageOpenPrice(Talasnica::Type::Packet);
			int getTicket(Talasnica::Type::Packet, unsigned int index);
		friend std::ostream& operator<<(std::ostream &os, Talasnica::OrderManager &orderManager);
	};	
}


