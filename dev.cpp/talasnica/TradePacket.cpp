#include "TradePacket.h"

#include <stdexcept>

using namespace std;

namespace Talasnica
{
	/**
	* statické promìnné
	**/

	const int  TradePacket::OP_BUY = 0; //Buying position. 
	const int  TradePacket::OP_SELL = 1; //Selling position. 
	const int  TradePacket::OP_BUYLIMIT = 2; //Buy limit pending position. 
	const int  TradePacket::OP_SELLLIMIT = 3; //Sell limit pending position. 
	const int  TradePacket::OP_BUYSTOP = 4; //Buy stop pending position. 
	const int  TradePacket::OP_SELLSTOP = 5; //Sell stop pending position. 
		// extended positions type
	const int  TradePacket::OP_PROFIT = 6; // positions in profit
	const int  TradePacket::OP_LOSS = 7; // loss positions 
	const int  TradePacket::OP_OPENED = 8; // all opened positions
	const int  TradePacket::OP_PREMOC = 9; // nezamèené pozice

	map<int, const string> TradePacket::descriptions = TradePacket::initialize_descriptions();
 	map<int, const string> TradePacket::initialize_descriptions(void)
 	{
		map<int, const string> map;

		map.insert(std::make_pair(OP_BUY,std::string("Buying position.")));
		map.insert(std::make_pair(OP_SELL,std::string("Selling position.")));
		map.insert(std::make_pair(OP_BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(OP_SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(OP_BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(OP_SELLSTOP,std::string("Sell stop pending position.")));
		map.insert(std::make_pair(OP_PROFIT,std::string("Pozice v profitu.")));
		map.insert(std::make_pair(OP_LOSS,std::string("Pozice ve ztrátì.")));
		map.insert(std::make_pair(OP_OPENED,std::string("Všechny pozice.")));
		map.insert(std::make_pair(OP_PREMOC,std::string("Nespárované pozice.")));

		return map;
 	}

/**

**/
	map<int, AverageOrder> TradePacket::initialize_packet(void)
	{
		map<int, AverageOrder> map;
		for(int i = TradePacket::OP_BUY; i <= TradePacket::OP_PREMOC; i++) {
			map.insert(std::make_pair(i,AverageOrder(TradePacket::descriptions[i])));
		}
		
		return map;
	}

	TradePacket::TradePacket(void)
	{
		packet = initialize_packet();
	}

	TradePacket::~TradePacket(void)
	{
	}

  void TradePacket::add(Order &order)
  {
		tradeList.insert(std::make_pair(order.ticket,order));
		packet[order.type].add(order);

		int index = NULL;
		if(order.totalProfit > 0) {
			index = TradePacket::OP_PROFIT;
		}
		else {
			index = TradePacket::OP_LOSS;
		}
		packet[index].add(order);
		
		if(order.type == TradePacket::OP_BUY || order.type == TradePacket::OP_SELL) {
			order.openPrice += 10;
			packet[TradePacket::OP_OPENED].add(order);
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
		
		/*map<int, Order>::iterator ordersIterator;
		for(ordersIterator = packet.tradeList.begin(); ordersIterator != packet.tradeList.end(); ordersIterator++) {
			os << ordersIterator->second << endl;
		}*/




		//int type = TradePacket::OP_BUY;
		//vector<Order *>::iterator ordersGroupIterator;

		//for(; type <= TradePacket::OP_PREMOC; type++) {

			//os << endl << "---------------------" << endl << TradePacket::descriptions[type] << endl;
		
			//for(int i = 0; i != packet.packet[type].size(); i++){
			/*for(ordersGroupIterator = packet.packet[type].begin(); ordersGroupIterator != packet.packet[type].end(); ordersGroupIterator++) {
				os << *(ordersGroupIterator) << endl;
			}*/
			/*for(ordersGroupIterator = packet.packet[type].begin(); ordersGroupIterator != packet.packet[type].end(); ordersGroupIterator++) {
				os << *(ordersGroupIterator) << endl;
			}*/

		//}

		return os;
	}
}