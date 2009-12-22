#include "Order.h"
#include "Exception.h"

using namespace std;

namespace Talasnica
{

	Order::Order(void)
	{
		cout << "Order::Order(void)" << endl;
	}

	Order::Order(const unsigned long ticket,
				 const string symbol,
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
				 const string comment,
				 const unsigned int magicNumber)
	{
		cout << "Order::Order(...)" << endl;
		this->ticket = ticket;
		this->symbol = symbol;
		this->openPrice = openPrice;
		this->type = type;
		this->lots = reverse(type) * lots;
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
		cout << "destructor Order::~Order(void)" << endl;
	}

	int Order::reverse(OperationType type) {
   
     switch (type) {
         case OP_BUY:
         case OP_BUYLIMIT:
         case OP_BUYSTOP:
            return 1;
         case OP_SELL:
         case OP_SELLLIMIT:
         case OP_SELLSTOP:
            return -1;
         default:
            throw Exception("Neplatný typ obchodu."); 
      }
}

	ostream& operator<<(ostream &os, const Order &order)
	{
		os << order.symbol;
		//os << ": " << TradePacket.names[order.type];
		os << " #" << order.ticket;
		os << " open on " << order.openTime;
		os << " price: " << order.openPrice;
		os << " lots " << order.lots;
		os << " total profit " << order.totalProfit;
		os << endl;
		
		
		/* nevypisuji zatím toto
		this->stopLoss = stopLoss;
		this->takeProfit = takeProfit;
		this->expiration = expiration;
		this->closeTime = closeTime;
		this->closePrice = closePrice;
		this->commission = commission;
		this->profit = profit;
		this->swap = swap;
		this->comment = comment;
		this->magicNumber = magicNumber;*/

								return os;
		
	} 

}