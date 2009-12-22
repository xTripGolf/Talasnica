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
		if(c >= PREMOC) {
			throw Exception("OrdersGroup se dostává mimo povolený rozsah.");
		}
		int t = (int)c;
		t++;
		c = (OrdersGroup)t; 
    return c;
	}

	map<OrdersGroup, const string> TradePacket::descriptions = TradePacket::initialize_descriptions();
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
		//map<OrdersGroup, AverageOrder> map;
		for(OrdersGroup i = BUY; i < PREMOC; i++) {
			/*map.*/ packet.insert(std::make_pair(i,AverageOrder(TradePacket::descriptions[i])));
			//map.insert(std::make_pair(i,AverageOrder()));
		}
		
		return packet/*map*/;
	}

	TradePacket::TradePacket(void)
	{
		cout << "TradePacket::TradePacket(void)" << endl;
		//descriptions = initialize_descriptions();
		//packet = initialize_packet();
	}

	TradePacket::~TradePacket(void)
	{
		cout << "TradePacket::~TradePacket(void)" << endl;
	}

  void TradePacket::add(Order order)
  {
		cout << "TradePacket::add(Order order)" << endl;
		tradeList.insert(std::make_pair(order.ticket,order));
	}

	void TradePacket::sort(void)
	{
		cout << "void TradePacket::sort(void)" << endl;

		try {
			initialize_packet();
		}
		catch(Exception e) {
			cerr << e.message << endl;
		}

		// projdeme tradelist
		map<int, Order>::iterator ordersIterator;
		for(ordersIterator = tradeList.begin(); ordersIterator != tradeList.end(); ordersIterator++) {
			Order & order = ordersIterator->second;
			OrdersGroup type = (OrdersGroup)order.type;
			packet[type].add(order);

			if(order.totalProfit > 0) {
				packet[PROFITED].add(order);
			}
			else {
				packet[LOSSED].add(order);
			}
		
			if(order.type == OP_BUY || order.type == OP_SELL) {
				packet[ALL_OPENED].add(order);
			}
		}

		map<OrdersGroup, AverageOrder>::iterator packetIterator;
		for(packetIterator = packet.begin(); packetIterator != packet.end(); packetIterator++) {
			packetIterator->second.sort();
		}

  }

	void TradePacket::reset(void) {
		cout << "TradePacket::add(Order &order)" << endl;
		tradeList.clear();
		packet.clear();
	}

	int TradePacket::count(void) {
		cout << "int TradePacket::count()" << endl;
		return tradeList.size();
	}

	//int count(void);
	int TradePacket::count(OrdersGroup type)
	{
		return packet[type].count;
	}
	double TradePacket::volume(void)
	{
		return 0;
	}
	double TradePacket::volume(OrdersGroup type)
	{
		return packet[type].volume;
	}
	double TradePacket::profit(void)
	{
		return 0;
	}
	double TradePacket::profit(OrdersGroup type)
	{
		return packet[type].profit;
	}
	double TradePacket::swap(void)
	{
		return 0;
	}
	double TradePacket::swap(OrdersGroup type)
	{
		return packet[type].swap;
	}
	double TradePacket::totalProfit(void)
	{
		return 0;
	}
	double TradePacket::totalProfit(OrdersGroup type)
	{
				return packet[type].totalProfit;
	}
	double TradePacket::averageOpenPrice(void)
	{
		return 0;
	}
	double TradePacket::averageOpenPrice(OrdersGroup type)
	{
		if(packet[type].jmenovatel != 0) {
			return packet[type].citatel / packet[type].jmenovatel;
		}
		return 0;
	}

	int TradePacket::getTicket(OrdersGroup type, unsigned int index){
		if(index > packet[type].orders.size()) {
			return 0;
		}
		return packet[type].orders[index]->ticket;
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