#include "StdAfx.h"
#include "Order.h"

using namespace std;

/*Talasnica::Order::Order(void)
{
	cout << "Talasnica::Order::Order(void)" << endl;
}*/

Talasnica::Order::Order(const unsigned long ticket,
				 const string symbol,
				 const unsigned int openTime,
				 Talasnica::Type::Order type,
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
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Order::Order((... hafo parametrù ...)" << endl;
		log.width(80);
		log.fill('-');
		log << "" << endl;
		log.fill(' ');
		log << "\tint __stdcall talasnica_addOrder(param orders)" << endl;
		log << "\t\tticket=" << ticket << endl;
		log << "\t\tsymbol=" << symbol << endl;
		log << "\t\topenTime=" << openTime << endl;
		log << "\t\ttype=" << type << endl;
		log << "\t\tlots=" << lots << endl;
		log << "\t\topenPrice=" << openPrice << endl;
		log << "\t\tstopLoss=" << stopLoss << endl;
		log << "\t\ttakeProfit=" << takeProfit << endl;
		log << "\t\texpiration=" << expiration << endl;
		log << "\t\tcloseTime=" << closeTime << endl;
		log << "\t\tclosePrice=" << closePrice << endl;
		log << "\t\tcommission=" << commission << endl;
		log << "\t\tprofit=" << profit << endl;
		log << "\t\tswap=" << swap << endl;
		log << "\t\tcomment=" << comment << endl;
		log << "\t\tmagicNumber=" << magicNumber << endl;
	#endif

		this->ticket = ticket;
		this->symbol = symbol;
		this->openPrice = openPrice;
		this->type = type;

		/*int reverse = type.reverse();
		this->lots = reverse * lots;*/
		this->lots = type.reverse(lots);

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
	
}

