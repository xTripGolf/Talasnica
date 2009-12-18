#include "TradePacket.h"

#include <stdexcept>

using namespace std;

namespace Talasnica
{
	TradePacket::TradePacket(void)
	{
		names.insert(std::make_pair(OP_BUY,std::string("Buying position.")));
		names.insert(std::make_pair(OP_SELL,std::string("Selling position.")));
		names.insert(std::make_pair(OP_BUYLIMIT,std::string("Buy limit pending position.")));
		names.insert(std::make_pair(OP_SELLLIMIT,std::string("Sell limit pending position.")));
		names.insert(std::make_pair(OP_BUYSTOP,std::string("Buy stop pending position.")));
		names.insert(std::make_pair(OP_SELLSTOP,std::string("Sell stop pending position.")));
		names.insert(std::make_pair(OP_PROFIT,std::string("Pozice v profitu.")));
		names.insert(std::make_pair(OP_LOSS,std::string("Pozice ve ztrátì.")));
		names.insert(std::make_pair(OP_OPENED,std::string("Všechny pozice.")));
		names.insert(std::make_pair(OP_PREMOC,std::string("Nespárované pozice.")));

	}

	TradePacket::~TradePacket(void)
	{
	}

  void TradePacket::add(Order &order)
  {
		tradeList.insert(std::make_pair(order.ticket,order));
		packet[order.type].push_back(order);

		int index = NULL;
		if(order.totalProfit > 0) {
			index = OP_PROFIT;
		}
		else {
			index = OP_LOSS;
		}
		packet[index].push_back(order);
		
		if(order.type == OP_BUY || order.type == OP_SELL) {
			order.openPrice += 10;
			packet[OP_OPENED].push_back(order);
		}
		
  }

	void TradePacket::reset(void) {
		tradeList.clear();
		packet.clear();
	}

	int TradePacket::count() {
		return tradeList.size();
	}

	ostream& operator<<(ostream &os, TradePacket &packet)
	{
		os << "*********** TALASNICA TRADE PACKET *********** " << endl;
		os << "Celkový poèet obchodù " << packet.count() << endl;
		os << " všechny obchody jsou zde " << endl;
		//copy(packet.tradeList.begin(),packet.tradeList.end(),ostream_iterator<Order>(cout,"\n"));
		//copy(packet.packet[OP_BUY].begin(),packet.packet[OP_BUY].end(),ostream_iterator<Order>(os,"\n"));
		
		map<int, Order>::iterator ordersIterator;
		for(ordersIterator = packet.tradeList.begin(); ordersIterator != packet.tradeList.end(); ordersIterator++) {
			os << ordersIterator->second << endl;
		}




		int type = OP_BUY;
		vector<Order>::iterator ordersGroupIterator;

		for(; type <= OP_PREMOC; type++) {

			os << endl << "---------------------" << endl << packet.names[type] << endl;
		
			for(ordersGroupIterator = packet.packet[type].begin(); ordersGroupIterator != packet.packet[type].end(); ordersGroupIterator++) {
				os << *(ordersGroupIterator) << endl;
			}

		}

		return os;
	}
}