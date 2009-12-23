#include "OrdersManager.h"

#include <stdexcept>
#include "dataType.h"
#include "Order.h"
#include "OrdersPacket.h"


using namespace std;

namespace Talasnica
{

	PacketFilter operator++(PacketFilter& c, int) {
		cout << "PacketFilter operator++(const PacketFilter& c) with " << c << endl;
		if(c >= PREMOC) {
			throw Exception("PacketFilter se dostává mimo povolený rozsah.");
		}
		int t = (int)c;
		t++;
		c = (PacketFilter)t; 
    return c;
	}

	OrdersManager::OrdersManager(void)
	{
		cout << "OrdersManager::OrdersManager(void)" << endl;
		//descriptions = initialize_descriptions();
		//packet = initialize_packet();
	}

	OrdersManager::~OrdersManager(void)
	{
		cout << "OrdersManager::~OrdersManager(void)" << endl;
	}

	/**

	**/
	map<PacketFilter, OrdersPacket> OrdersManager::initialize_packet(void)
	{
		cout << "map<int, OrdersPacket> OrdersManager::initialize_packet(void)" << endl;
		//map<PacketFilter, OrdersPacket> map;
		for(PacketFilter i = BUY; i < PREMOC; i++) {
			/*map.*/ packet.insert(std::make_pair(i,OrdersPacket(OrdersManager::descriptions[i])));
			//map.insert(std::make_pair(i,OrdersPacket()));
		}
		
		return packet/*map*/;
	}

  void OrdersManager::add(Order order)
  {
		cout << "OrdersManager::add(Order order)" << endl;
		ordersPool.insert(std::make_pair(order.ticket,order));
	}

	void OrdersManager::sort(void)
	{
		cout << "void OrdersManager::sort(void)" << endl;

		try {
			initialize_packet();
		}
		catch(Exception e) {
			cerr << e.message << endl;
		}

		// projdeme tradelist
		map<int, Order>::iterator ordersIterator;
		for(ordersIterator = ordersPool.begin(); ordersIterator != ordersPool.end(); ordersIterator++) {
			Order & order = ordersIterator->second;
			PacketFilter type = (PacketFilter)order.type;
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

		map<PacketFilter, OrdersPacket>::iterator packetIterator;
		for(packetIterator = packet.begin(); packetIterator != packet.end(); packetIterator++) {
			packetIterator->second.sort();
		}

  }

	void OrdersManager::reset(void) {
		cout << "OrdersManager::add(Order &order)" << endl;
		ordersPool.clear();
		packet.clear();
	}

	int OrdersManager::count(void) {
		cout << "int OrdersManager::count()" << endl;
		return ordersPool.size();
	}

	//int count(void);
	int OrdersManager::count(PacketFilter type)
	{
		return packet[type].count;
	}
	double OrdersManager::volume(void)
	{
		return 0;
	}
	double OrdersManager::volume(PacketFilter type)
	{
		return packet[type].volume;
	}
	double OrdersManager::profit(void)
	{
		return 0;
	}
	double OrdersManager::profit(PacketFilter type)
	{
		return packet[type].profit;
	}
	double OrdersManager::swap(void)
	{
		return 0;
	}
	double OrdersManager::swap(PacketFilter type)
	{
		return packet[type].swap;
	}
	double OrdersManager::totalProfit(void)
	{
		return 0;
	}
	double OrdersManager::totalProfit(PacketFilter type)
	{
				return packet[type].totalProfit;
	}
	double OrdersManager::averageOpenPrice(void)
	{
		return 0;
	}
	double OrdersManager::averageOpenPrice(PacketFilter type)
	{
		if(packet[type].jmenovatel != 0) {
			return packet[type].citatel / packet[type].jmenovatel;
		}
		return 0;
	}

	int OrdersManager::getTicket(PacketFilter type, unsigned int index){
		if(index > packet[type].orders.size()) {
			return 0;
		}
		return packet[type].orders[index]->ticket;
	}

	string OrdersManager::getPacketName(PacketFilter type){
		return OrdersManager::names[type];
	}
	string OrdersManager::getPacketDescription(PacketFilter type){
		return OrdersManager::descriptions[type];
	}

	ostream& operator<<(ostream &os, OrdersManager &packet)
	{
		os << "*********** TALASNICA TRADE PACKET *********** " << endl;
		os << "Celkový poèet obchodù " << packet.count() << endl;
		os << " všechny obchody jsou zde " << endl;

		//copy(packet.ordersPool.begin(),packet.ordersPool.end(),ostream_iterator<Order>(cout,"\n"));
		//copy(packet.packet[OP_BUY].begin(),packet.packet[OP_BUY].end(),ostream_iterator<Order>(os,"\n"));
		
		map<int, Order>::iterator ordersIterator;
		for(ordersIterator = packet.ordersPool.begin(); ordersIterator != packet.ordersPool.end(); ordersIterator++) {
			os << ordersIterator->second << endl;
		}

		map<PacketFilter, OrdersPacket>::iterator averageOrdersIterator;
		for(averageOrdersIterator = packet.packet.begin(); averageOrdersIterator != packet.packet.end(); averageOrdersIterator++) {
			os << averageOrdersIterator->second << endl;
		}
		return os;
	}
}