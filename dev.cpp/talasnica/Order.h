#pragma once

#include <string>
#include <iostream>
#include <sstream>

//#include "TradePacket.h"

using namespace std;

namespace Talasnica
{
	class Order
	{
	//private:
	public:
		unsigned long ticket;
		string symbol;
		unsigned int openTime;
		unsigned short type;
		double lots;
		double openPrice;
		double stopLoss;
		double takeProfit;
		unsigned int expiration;
		unsigned int closeTime;
		double closePrice;
		double commission;
		double profit;
		double swap;
		string comment;
		unsigned int magicNumber;

		//
		double totalProfit;

	public:
		Order(void);
		Order(const unsigned long ticket,
				 const string symbol,
				 const unsigned int openTime,
				 const unsigned short type,
				 const double lots,
				 const double openPrice,
				 const double stopLoss,
				 const double takeProfit,
				 const unsigned int expiration,
				 const unsigned int closeTime,
				 const double closePrice,
				 const double commission,
				 const double profit,
				 const double swap,
				 const string comment,
				 const unsigned int magicNumber);
		~Order(void);
		int Order::getTicket(void);

	friend ostream& operator<<(ostream &os, Order &objekt);
	friend bool operator<(const Order& a, const Order& b);
	friend bool operator>(const Order& a, const Order& b);
	friend bool operator==(const Order& a, const Order& b);
	//friend Talasnica::TradePacket::add(Order order);
	};
}
