#pragma once

#include <string>
//#include <map>
//#include <vector>
#include <iostream>


namespace Talasnica
{

	class TradePacket;
	class Order;

	class AverageOrder
	{
	private:
		//double citatel;
		//double jmenovatel;
		//double lots;
		int type;
		std::string description;
	public:
		AverageOrder(void);
		AverageOrder(std::string);
		~AverageOrder(void);
		void add(Order&);
	friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
	friend std::ostream& operator<<(std::ostream &os, const Order &order);
	};

}
