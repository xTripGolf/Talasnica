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
		os << "\t\tticket=" << order.ticket << endl;
		os << "\t\tsymbol=" << order.symbol << endl;
		os << "\t\topenTime=" << order.openTime << endl;

		//string typeDesc("...");
		//os << "\t\ttype=" << order.type << "(" << typeDesc << ")" << endl;

		os << "\t\ttype=" << order.type << endl;
		os << "\t\tlots=" << order.lots << endl;
		os << "\t\topenPrice=" << order.openPrice << endl;
		os << "\t\tstopLoss=" << order.stopLoss << endl;
		os << "\t\ttakeProfit=" << order.takeProfit << endl;
		os << "\t\texpiration=" << order.expiration << endl;
		os << "\t\tcloseTime=" << order.closeTime << endl;
		os << "\t\tclosePrice=" << order.closePrice << endl;
		os << "\t\tcommission=" << order.commission << endl;
		os << "\t\tprofit=" << order.profit << endl;
		os << "\t\tswap=" << order.swap << endl;
		os << "\t\tcomment=" << order.comment << endl;
		os << "\t\tmagicNumber=" << order.magicNumber << endl;

	return os;
		
}

ostream& Talasnica::Type::operator<<(std::ostream &os, const Talasnica::Type::Order &orderType)
{
	os << "order type: " << orderType.value << endl;
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

	::std::map<Talasnica::Type::PacketFilter, Talasnica::OrdersPacket>::iterator packetIterator;
	for(packetIterator = ordersManager.packet.begin(); packetIterator != ordersManager.packet.end(); packetIterator++) {
		os << packetIterator->second << endl;
	}
	return os;
}

ostream& Talasnica::operator<<(ostream &os, const OrdersPacket &packet)
{

	//os << endl << "---------------------" << endl << packet.description << endl;

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

ostream& Talasnica::Type::operator<<(ostream &os, const Talasnica::Type::PacketFilter &packetFilter){
	os << "packetFilter" << endl;
	return os;
}