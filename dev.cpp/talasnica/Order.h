#pragma once

#include "talasnica.h"
#include "type.h"

namespace Talasnica
{

	class Order
	{
	private:
	//public:
		unsigned long ticket;
		std::string symbol;
		unsigned int openTime;
		Talasnica::Type::Order type;
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

	public:
		//Order(void);
		Order(const unsigned long ticket,
			const std::string symbol,
				 const unsigned int openTime,
				 /*const*/ Talasnica::Type::Order type,
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

	friend ::std::ostream& operator<<(::std::ostream &os, const Talasnica::Order &order);
	friend class Talasnica::OrdersManager;
	friend class Talasnica::OrdersPacket;
	friend class Talasnica::Sort::ByOpenPrice;
	};
}
