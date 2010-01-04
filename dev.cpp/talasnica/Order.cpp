#include "Order.h"

using namespace std;

Talasnica::Order::Order(void)
{
	cout << "Talasnica::Order::Order(void)" << endl;
}

Talasnica::Order::Order(const unsigned long ticket,
				 const string symbol,
				 const unsigned int openTime,
				 const Talasnica::Enum::Order type,
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
		cout << "Talasnica::Order::Order(...)" << endl;
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

Talasnica::Order::~Order(void)
{
	cout << "destructor Order::~Order(void)" << endl;
}

int Talasnica::Order::reverse(Talasnica::Enum::Order type) {
   switch (type) {
		case Talasnica::Enum::OP_BUY:
    case Talasnica::Enum::OP_BUYLIMIT:
    case Talasnica::Enum::OP_BUYSTOP:
			return 1;
    case Talasnica::Enum::OP_SELL:
    case Talasnica::Enum::OP_SELLLIMIT:
    case Talasnica::Enum::OP_SELLSTOP:
			return -1;
    default:
			throw Talasnica::Exception::EnumOverFlow("Neplatný typ obchodu."); 
   }
}
