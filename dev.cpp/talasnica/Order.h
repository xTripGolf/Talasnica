#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "dataType.h"
#include "TradePacket.h"

namespace Talasnica
{

	class TradePacket;
	class AverageOrder;

	class Order
	{
	private:
	//public:
		unsigned long ticket;
		std::string symbol;
		unsigned int openTime;
		/*unsigned short*/ OperationType type;
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
		std::string comment;
		unsigned int magicNumber;

		//
		double totalProfit;

	public:
		Order(void);
		Order(const unsigned long ticket,
			const std::string symbol,
				 const unsigned int openTime,
				 const OperationType type,
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
				 const std::string comment,
				 const unsigned int magicNumber);
		~Order(void);
		int Order::getTicket(void);

	friend std::ostream& operator<<(std::ostream &os, const Order &order);
	friend bool operator<(const Order& a, const Order& b);
	friend bool operator>(const Order& a, const Order& b);
	friend bool operator==(const Order& a, const Order& b);
	friend class Talasnica::TradePacket;
	friend class Talasnica::AverageOrder;
	};
}
