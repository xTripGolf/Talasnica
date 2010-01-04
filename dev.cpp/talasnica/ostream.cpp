#include "ostream.h"

using namespace std;

std::ostream& Talasnica::Exception::operator<<(::std::ostream &os, const Talasnica::Exception::Exception &e)
{
	//os << __FILE__ << __LINE__ << endl;
	os << "ERROR: " << e.message << endl;
	return os;
}

ostream& Talasnica::operator<<(ostream &os, const Talasnica::Order &order)
{
	os << order.symbol;
	//os << ": " << OrdersManager.names[order.type];
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

ostream& Talasnica::operator<<(ostream &os, Talasnica::OrdersManager &ordersManager)
{
	os << "*********** TALASNICA TRADE ordersManager *********** " << endl;
	os << "Celkový poèet obchodù " << ordersManager.count() << endl;
	os << " všechny obchody jsou zde " << endl;

	//copy(ordersManager.ordersPool.begin(),ordersManager.ordersPool.end(),ostream_iterator<Order>(cout,"\n"));
	//copy(ordersManager.packet[OP_BUY].begin(),ordersManager.packet[OP_BUY].end(),ostream_iterator<Order>(os,"\n"));
		
	map<int, Talasnica::Order>::iterator ordersIterator;
	for(ordersIterator = ordersManager.ordersPool.begin(); ordersIterator != ordersManager.ordersPool.end(); ordersIterator++) {
		os << ordersIterator->second << endl;
	}

	::std::map<Talasnica::Enum::PacketFilter, Talasnica::OrdersPacket>::iterator packetIterator;
	for(packetIterator = ordersManager.packet.begin(); packetIterator != ordersManager.packet.end(); packetIterator++) {
		os << packetIterator->second << endl;
	}
	return os;
}

ostream& Talasnica::operator<<(ostream &os, const OrdersPacket &packet)
{

	os << endl << "---------------------" << endl << packet.description << endl;

	os << "count: " << packet.count << endl;
	os << "volume: " << packet.volume << endl;
	os << "profit: " << packet.profit << endl;
	os << "swap: " << packet.swap << endl;
	
	/*vector<Order *>::iterator ordersIterator;
	for(ordersIterator = packet.orders.begin(); ordersIterator != packet.orders.end(); ordersIterator++) {
			os << *(ordersIterator) << endl;
	}*/

	for(int i =0; i != packet.orders.size(); i++) {
		os << *(packet.orders[i]) << endl;
	}

	return os;
		
}