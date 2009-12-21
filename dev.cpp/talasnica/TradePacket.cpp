#include "TradePacket.h"

#include <stdexcept>
#include "dataType.h"
#include "Order.h"
#include "AverageOrder.h"


using namespace std;

namespace Talasnica
{

	OrdersGroup operator++(OrdersGroup& c, int) {
		cout << "OrdersGroup operator++(const OrdersGroup& c) with " << c << endl;
		int t = (int)c;
		t++;
		c = (OrdersGroup)t;
    return c;
	}

	//map<int, const string> TradePacket::descriptions = TradePacket::initialize_descriptions();
 	map<OrdersGroup, const string> TradePacket::initialize_descriptions(void)
 	{
		cout << "map<int, const string> TradePacket::initialize_descriptions(void)" << endl;

		map<OrdersGroup, const string> map;

		map.insert(std::make_pair(BUY,std::string("Buying position.")));
		map.insert(std::make_pair(SELL,std::string("Selling position.")));
		map.insert(std::make_pair(BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(SELLSTOP,std::string("Sell stop pending position.")));
		map.insert(std::make_pair(PROFITED,std::string("Pozice v profitu.")));
		map.insert(std::make_pair(LOSSED,std::string("Pozice ve ztrátì.")));
		map.insert(std::make_pair(ALL_OPENED,std::string("Všechny pozice.")));
		map.insert(std::make_pair(PREMOC,std::string("Nespárované pozice.")));

		return map;
 	}

/**

**/
	map<OrdersGroup, AverageOrder> TradePacket::initialize_packet(void)
	{
		cout << "map<int, AverageOrder> TradePacket::initialize_packet(void)" << endl;
		map<OrdersGroup, AverageOrder> map;
		for(OrdersGroup i = BUY; i <= PREMOC; i++) {
			map.insert(std::make_pair(i,AverageOrder(TradePacket::descriptions[i])));
			//map.insert(std::make_pair(i,AverageOrder()));
		}
		
		return map;
	}

	TradePacket::TradePacket(void)
	{
		cout << "TradePacket::TradePacket(void)" << endl;
		descriptions = initialize_descriptions();
		packet = initialize_packet();
	}

	TradePacket::~TradePacket(void)
	{
		cout << "TradePacket::~TradePacket(void)" << endl;
	}

  void TradePacket::add(Order &order)
  {
		cout << "TradePacket::add(Order &order)" << endl;
		tradeList.insert(std::make_pair(order.ticket,order));

		OrdersGroup type = (OrdersGroup)order.type;

		packet[type].add(order);

		OrdersGroup index;
		if(order.totalProfit > 0) {
			index = PROFITED;
		}
		else {
			index = LOSSED;
		}
		packet[index].add(order);
		
		if(order.type == OP_BUY || order.type == OP_SELL) {
			order.openPrice += 10;
			packet[ALL_OPENED].add(order);
		}
		
  }

	void TradePacket::reset(void) {
		cout << "TradePacket::add(Order &order)" << endl;
		tradeList.clear();
		packet.clear();
	}

	int TradePacket::count() {
		cout << "int TradePacket::count()" << endl;
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

		map<OrdersGroup, AverageOrder>::iterator averageOrdersIterator;
		for(averageOrdersIterator = packet.packet.begin(); averageOrdersIterator != packet.packet.end(); averageOrdersIterator++) {
			os << averageOrdersIterator->second << endl;
		}
		return os;
	}
}