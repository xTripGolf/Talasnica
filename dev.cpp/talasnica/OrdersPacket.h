#pragma once

#include <string>
//#include <map>
#include <vector>
//#include <iostream>
#include <algorithm>

#include "talasnica.h"
#include "Order.h"
#include "OrdersSort.h"

namespace Talasnica
{

	class OrdersManager;
	class Order;

	class OrdersPacket
	{
	private:
		double citatel;
		double jmenovatel;
		int count;
		double volume;
		double profit;
		double swap;
		double totalProfit;
		int type;
		std::string description;
		std::vector<Order *> orders;
	public:
		OrdersPacket(void);
		OrdersPacket(std::string);
		~OrdersPacket(void);
		void add(Order &);
		void sort(void);
	friend std::ostream& operator<<(std::ostream &os, const OrdersPacket &averageOrder);
	friend std::ostream& operator<<(std::ostream &os, OrdersManager &objekt);
	friend std::ostream& operator<<(std::ostream &os, const Order &order);
	friend OrdersManager;
	};

}
