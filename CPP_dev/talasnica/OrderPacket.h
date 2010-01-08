#pragma once

#include <vector>

namespace Talasnica
{

	class OrderManager;
	class Order;

	class OrderPacket
	{
	typedef std::vector<Order *> OrderPacketVector;
	private:
		double citatel;
		double jmenovatel;
		int count;
		double volume;
		double profit;
		double swap;
		double totalProfit;
		OrderPacketVector orders;
	public:
		OrderPacket(void);
		~OrderPacket(void);
		void add(Order &);
		void sort(void);
	friend std::ostream& operator<<(std::ostream &os, OrderPacket &packet);
	//friend std::ostream& operator<<(std::ostream &os, OrderManager &objekt);
	//friend std::ostream& operator<<(std::ostream &os, const Order &order);
	friend OrderManager;
	};

}
