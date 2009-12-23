#pragma once

#include <string>
//#include <map>
#include <vector>
#include <iostream>

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

	class OrderSort {
		public:
				bool operator()(Order * o1, Order * o2);
	};

}
