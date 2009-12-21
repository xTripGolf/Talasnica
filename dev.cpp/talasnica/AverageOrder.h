#pragma once

#include <string>
//#include <map>
#include <vector>
#include <iostream>

namespace Talasnica
{

	class TradePacket;
	class Order;

	class AverageOrder
	{
	private:
		double citatel = 0;
		double jmenovatel = 0;
		//double lots;
		int type;
		std::string description;
		std::vector<Order *> orders;
	public:
		AverageOrder(void);
		AverageOrder(std::string);
		~AverageOrder(void);
		void add(Order &);
		void sort(void);
	friend std::ostream& operator<<(std::ostream &os, const AverageOrder &averageOrder);
	friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
	friend std::ostream& operator<<(std::ostream &os, const Order &order);
	};

	class OrderSort {
		public:
				bool operator()(Order * o1, Order * o2);
	};

}
