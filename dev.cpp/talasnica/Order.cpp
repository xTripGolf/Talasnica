#include "Order.h"

namespace Talasnica
{

	Order::Order(void)
	{
	}

	Order::Order(const unsigned long ticket,
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
				 const unsigned int magicNumber)
	{
		this->ticket = ticket;
		this->symbol = symbol;
		this->openPrice = openPrice;
		this->type = type;
		this->lots = lots;
		this->openPrice = openPrice;
		this->stopLoss = stopLoss;
		this->takeProfit = takeProfit;
		this->expiration = expiration;
		this->closeTime = closeTime;
		this->closePrice = closePrice;
		this->commission = commission;
		this->profit = profit;
		this->swap = swap;
		this->comment = comment;
		this->magicNumber = magicNumber;

		this->totalProfit = commission + profit + swap;
	}

	Order::~Order(void)
	{
	}

	int Order::getTicket(void) {
		return ticket;
	}

	/*string Order::toString(void) {

		 stringstream proud(ios_base::out);

		 proud << "order " << ticket << " open on " << openPrice;
		 return proud.str();
	   
	}*/

	bool operator<(const Order& a, const Order& b) {
    return a.openPrice < b.openPrice;
	}

	bool operator==(const Order& a, const Order& b) {
    return a.openPrice == b.openPrice;
	}

	bool operator>(const Order& a, const Order& b) {
    return a.openPrice > b.openPrice;
	}

	ostream& operator<<(ostream &os, Order &objekt)
	{
		return(os << "order " << objekt.ticket << " open on " << objekt.openPrice);
	} 

}