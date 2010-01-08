#include "StdAfx.h"
#include "ostream.h"

using namespace std;

std::ostream& Talasnica::Exception::operator<<(::std::ostream &os, const Talasnica::Exception::Exception &e)
{
	os << "ERROR: " << e.message << endl;
	return os;
}

ostream& Talasnica::Type::operator<<(std::ostream &os, const Talasnica::Type::Order &orderType)
{
	os << "#" << orderType.value << ": " << orderType.names[orderType.value];
	return os;
}

ostream& Talasnica::Type::operator<<(std::ostream &os, const Talasnica::Type::Packet &type)
{
	os << "#" << type.value << ": " << type.names[type.value];
	return os;
}

ostream& Talasnica::operator<<(ostream &os, const Talasnica::Order &order)
{
	
	//Zapisnicar::Table table;

	/*table.addColumn("ticket", 12);
	table.addColumn("symbol", 12);
	table.addColumn("openTime", 12);
	table.addColumn("type", 12);
	table.addColumn("lots", 12);
	table.addColumn("openPrice", 12);
	table.addColumn("stopLoss", 12);
	table.addColumn("takeProfit", 12);
	table.addColumn("expiration", 12);
	table.addColumn("closeTime", 12);
	table.addColumn("commission", 12);
	table.addColumn("profit", 12);
	table.addColumn("swap", 12);
	table.addColumn("comment", 12);
	table.addColumn("magicNumber", 12);*/

	//os << table.head();

	//os << table.format(os);// << endl << table.format() << endl;

	int symbolWidth = 8;
	int ticketWidth = 12;
	int openTimeWidth = 12;
	int typeWidth = 32;
	int lotsWidth = 12;
	int openPriceWidth = 12;
	int stopLossWidth = 12;
	int takeProfitWidth = 12;
	int expirationWidth = 12;
	int closeTimeWidth = 12;
	int closePriceWidth = 12;
	int commissionWidth = 12;
	int profitWidth = 12;
	int swapWidth = 12;
	int commentWidth = 12;
	int magicNumberWidth = 12;

	os << setw(symbolWidth) << "symbol";
	os << setw(ticketWidth) << "ticket";
	os << setw(openTimeWidth) << "openTime";
	os << setw(typeWidth) << "type";
	os << setw(lotsWidth) << "lots";
	os << setw(openPriceWidth) << "openPrice";
	os << setw(stopLossWidth) << "stopLoss";
	os << setw(takeProfitWidth) << "takeProfit";
	os << setw(expirationWidth) << "expiration";
	os << setw(closeTimeWidth) << "closeTime";
	os << setw(closePriceWidth) << "closePrice";
	os << setw(commissionWidth) << "commission";
	os << setw(profitWidth) << "profit";
	os << setw(swapWidth) << "swap";
	os << setw(commentWidth) << "comment";
	os << setw(magicNumberWidth) << "magicNumber";
	os << endl;

	//os << setw(wc1) << "count" << setw(wc2) << "volume" << setw(wc3) << "profit" << setw(wc4) << "swap" << endl;
	//os << setw(wc1) << packet.count << setw(wc2) << packet.volume << setw(wc3) << packet.profit << setw(wc4) << packet.swap << endl;
	
		os << setw(symbolWidth) << order.symbol;
		os << setw(ticketWidth) << order.ticket;
		os << setw(openTimeWidth) << order.openTime;

		//string typeDesc("...");
		//os << setw(typeWidth) << order.type << "(" << typeDesc << ")";

		stringstream s(ios_base::out);
		s << order.type;

		os << setw(typeWidth) << s.str();
		os << setw(lotsWidth) << order.lots;
		os << setw(openPriceWidth) << order.openPrice;
		os << setw(stopLossWidth) << order.stopLoss;
		os << setw(takeProfitWidth) << order.takeProfit;
		os << setw(expirationWidth) << order.expiration;
		os << setw(closeTimeWidth) << order.closeTime;
		os << setw(closePriceWidth) << order.closePrice;
		os << setw(commissionWidth) << order.commission;
		os << setw(profitWidth) << order.profit;
		os << setw(swapWidth) << order.swap;
		os << setw(commentWidth) << order.comment;
		os << setw(magicNumberWidth) << order.magicNumber;
		os << endl;
	return os;	
}

ostream& Talasnica::operator<<(ostream &os, Talasnica::OrderManager &orderManager)
{
	os << "*********** TALASNICA TRADE orderManager *********** " << endl;
	os << "Celkový poèet obchodù v ordersPool " << orderManager.ordersPool.size() << endl;
	os << " všechny obchody jsou zde " << endl;
		
	Talasnica::OrderManager::OrdersPoolMap::iterator poolIterator;
	for(poolIterator = orderManager.ordersPool.begin(); poolIterator != orderManager.ordersPool.end(); poolIterator++) {
		os << poolIterator->second << endl;
	}

	/*::std::map<Talasnica::Type::PacketFilter, Talasnica::OrderPacket>::iterator packetIterator;
	for(packetIterator = orderManager.packet.begin(); packetIterator != orderManager.packet.end(); packetIterator++) {
		os << packetIterator->second << endl;
	}*/
	return os;
}

ostream& Talasnica::operator<<(ostream &os, Talasnica::OrderPacket &packet)
{

	os.width(80);
	os.fill('-');
	os << "-" << endl;
	os.fill(' ');

	int wc1 = 12;
	int wc2 = 12;
	int wc3 = 12;
	int wc4 = 12;

	os << setw(wc1) << "count" << setw(wc2) << "volume" << setw(wc3) << "profit" << setw(wc4) << "swap" << endl;
	os << setw(wc1) << packet.count << setw(wc2) << packet.volume << setw(wc3) << packet.profit << setw(wc4) << packet.swap << endl;
	os << "orders" << endl;

	Talasnica::OrderPacket::OrderPacketVector::iterator ordersIterator;
	
	for(ordersIterator = packet.orders.begin(); ordersIterator != packet.orders.end(); ordersIterator++) {
			//Talasnica::Order order = **(ordersIterator);
			os << **(ordersIterator) << endl;
			//os << ordersIterator->ticket << endl;
	}

	/*for(int i =0; i != packet.orders.size(); i++) {
		os << *(packet.orders[i]) << endl;
	}*/

	return os;
		
}

