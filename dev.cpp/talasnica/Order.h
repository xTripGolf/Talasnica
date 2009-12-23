#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "dataType.h"
#include "OrdersManager.h"

namespace Talasnica
{

	class OrdersManager;
	class OrdersPacket;
	class OrderSort;

	class Order
	{
	private:
	//public:
		unsigned long ticket;
		std::string symbol;
		unsigned int openTime;
		OrderType type;
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

		double totalProfit;

		/**
		* vrací 1 pro long pozice a -1 pro short pozice
		**/
		int reverse(OrderType);

	public:
		Order(void);
		Order(const unsigned long ticket,
			const std::string symbol,
				 const unsigned int openTime,
				 const OrderType type,
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
	friend class Talasnica::OrdersManager;
	friend class Talasnica::OrdersPacket;
	friend class Talasnica::OrderSort;
	};
}
