#include "StdAfx.h"
#include "OrderPacket.h"

using namespace std;

Talasnica::OrderPacket::OrderPacket()
{
	citatel = 0;
	jmenovatel = 0;
	count = 0;
	volume = 0;
	profit = 0;
	swap = 0;
	totalProfit = 0;
}

Talasnica::OrderPacket::~OrderPacket(void)
{
	
}

void Talasnica::OrderPacket::add(Order &order){
	
	orders.push_back(&order);
	citatel += order.lots * order.openPrice;
	jmenovatel += order.lots;
	count ++;
	volume += order.lots;
	profit += order.profit;
	swap += order.swap;
	totalProfit += order.totalProfit;
}

void Talasnica::OrderPacket::sort(void)
{
	Talasnica::Sort::ByOpenPrice sort;
	std::sort(orders.begin(),orders.end(),sort);

	/*for(unsigned int i = 0; i < orders.size(); i++){
		cout << orders[i] << endl;
	}*/
}

