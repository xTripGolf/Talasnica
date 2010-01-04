#include "OrdersManager.h"

#include <stdexcept>
#include "talasnica.h"
#include "Order.h"
#include "OrdersPacket.h"

using namespace std;


Talasnica::OrdersManager::OrdersManager(void)
{
	cout << "OrdersManager::OrdersManager(void)" << endl;
}

Talasnica::OrdersManager::~OrdersManager(void)
{
	cout << "OrdersManager::~OrdersManager(void)" << endl;
}

	/**

	**/
map<Talasnica::Enum::PacketFilter, Talasnica::OrdersPacket> Talasnica::OrdersManager::initialize_packet(void)
{
	cout << "map<int, OrdersPacket> OrdersManager::initialize_packet(void)" << endl;
	
	for(Talasnica::Enum::PacketFilter i = Talasnica::Enum::BUY; i < Talasnica::Enum::PREMOC; i++) {
			packet.insert(std::make_pair(i,OrdersPacket(OrdersManager::descriptions[i])));
	}
	return packet;
}

void Talasnica::OrdersManager::add(Order order)
{
	cout << "OrdersManager::add(Order order)" << endl;
	ordersPool.insert(std::make_pair(order.ticket,order));
}

void Talasnica::OrdersManager::sort(void)
{
	cout << "void OrdersManager::sort(void)" << endl;

	try {
		initialize_packet();
	}
	catch(Talasnica::Exception::EnumOverFlow e) {
		cerr << e.message << endl;
	}

	// projdeme ordersPool
	map<int, Order>::iterator ordersIterator;
	for(ordersIterator = ordersPool.begin(); ordersIterator != ordersPool.end(); ordersIterator++) {
		Order & order = ordersIterator->second;
		Talasnica::Enum::PacketFilter packetFilter = Talasnica::PacketFilterEnum(order.type);
		packet[packetFilter].add(order);

		if(order.totalProfit > 0) {
			packet[Talasnica::Enum::PROFITED].add(order);
		}
		else {
			packet[Talasnica::Enum::LOSSED].add(order);
		}
		
		if(order.type == Talasnica::Enum::OP_BUY || order.type == Talasnica::Enum::OP_SELL) {
			packet[Talasnica::Enum::ALL_OPENED].add(order);
		}
	}

	map<Talasnica::Enum::PacketFilter, OrdersPacket>::iterator packetIterator;
	for(packetIterator = packet.begin(); packetIterator != packet.end(); packetIterator++) {
		packetIterator->second.sort();
	}
}

void Talasnica::OrdersManager::reset(void) {
	cout << "OrdersManager::add(Order &order)" << endl;
	ordersPool.clear();
	packet.clear();
}

int Talasnica::OrdersManager::count(void) {
	cout << "int OrdersManager::count()" << endl;
	return ordersPool.size();
}

	//int count(void);
	int Talasnica::OrdersManager::count(Talasnica::Enum::PacketFilter packetFilter)
	{
		return packet[packetFilter].count;
	}
	double Talasnica::OrdersManager::volume(void)
	{
		return 0;
	}
	double Talasnica::OrdersManager::volume(Talasnica::Enum::PacketFilter packetFilter)
	{
		return packet[packetFilter].volume;
	}
	double Talasnica::OrdersManager::profit(void)
	{
		return 0;
	}
	double Talasnica::OrdersManager::profit(Talasnica::Enum::PacketFilter packetFilter)
	{
		return packet[packetFilter].profit;
	}
	double Talasnica::OrdersManager::swap(void)
	{
		return 0;
	}
	double Talasnica::OrdersManager::swap(Talasnica::Enum::PacketFilter packetFilter)
	{
		return packet[packetFilter].swap;
	}
	double Talasnica::OrdersManager::totalProfit(void)
	{
		return 0;
	}
	double Talasnica::OrdersManager::totalProfit(Talasnica::Enum::PacketFilter packetFilter)
	{
				return packet[packetFilter].totalProfit;
	}
	double Talasnica::OrdersManager::averageOpenPrice(void)
	{
		return 0;
	}
	double Talasnica::OrdersManager::averageOpenPrice(Talasnica::Enum::PacketFilter packetFilter)
	{
		if(packet[packetFilter].jmenovatel != 0) {
			return packet[packetFilter].citatel / packet[packetFilter].jmenovatel;
		}
		return 0;
	}

	int Talasnica::OrdersManager::getTicket(Talasnica::Enum::PacketFilter packetFilter, unsigned int index){
		if(index > packet[packetFilter].orders.size()) {
			return 0;
		}
		return packet[packetFilter].orders[index]->ticket;
	}

	string Talasnica::OrdersManager::getPacketName(Talasnica::Enum::PacketFilter packetFilter){
		return Talasnica::OrdersManager::names[packetFilter];
	}
	string Talasnica::OrdersManager::getPacketDescription(Talasnica::Enum::PacketFilter packetFilter){
		return Talasnica::OrdersManager::descriptions[packetFilter];
	}

ostream& Talasnica::operator<<(ostream &os, ::Talasnica::OrdersManager &ordersManager)
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