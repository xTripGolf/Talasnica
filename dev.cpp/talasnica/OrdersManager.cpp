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
map<Talasnica::Type::PacketFilter, Talasnica::OrdersPacket> Talasnica::OrdersManager::initialize_packet(void)
{
	cout << "map<Talasnica::Type::PacketFilter, OrdersPacket> OrdersManager::initialize_packet(void)" << endl;
	
	//for(int i = Talasnica::Type::PacketFilter.begin(); i < Talasnica::Type::PacketFilter.end(); i++) {
	for(int i = 0; i < 10; i++) {
			packet.insert(std::make_pair(Talasnica::Type::PacketFilter(i),OrdersPacket()));
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
		Talasnica::Type::PacketFilter packetFilter(order.type);
		packet[packetFilter].add(order);

		if(order.totalProfit > 0) {
			packet[Talasnica::Type::PacketFilter::PROFITED].add(order);
		}
		else {
			packet[Talasnica::Type::PacketFilter::LOSSED].add(order);
		}
		
		if(order.type == Talasnica::Type::Order::BUY || order.type == Talasnica::Type::Order::SELL) {
			packet[Talasnica::Type::PacketFilter::ALL_OPENED].add(order);
		}
	}

	map<Talasnica::Type::PacketFilter, OrdersPacket>::iterator packetIterator;
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

int Talasnica::OrdersManager::count(Talasnica::Type::PacketFilter packetFilter)
{
	return packet[packetFilter].count;
}
double Talasnica::OrdersManager::volume(void)
{
	return 0;
}
double Talasnica::OrdersManager::volume(Talasnica::Type::PacketFilter packetFilter)
{
	return packet[packetFilter].volume;
}
double Talasnica::OrdersManager::profit(void)
{
	return 0;
}
double Talasnica::OrdersManager::profit(Talasnica::Type::PacketFilter packetFilter)
{
	return packet[packetFilter].profit;
}
double Talasnica::OrdersManager::swap(void)
{
	return 0;
}
double Talasnica::OrdersManager::swap(Talasnica::Type::PacketFilter packetFilter)
{
	return packet[packetFilter].swap;
}
double Talasnica::OrdersManager::totalProfit(void)
{
	return 0;
}
double Talasnica::OrdersManager::totalProfit(Talasnica::Type::PacketFilter packetFilter)
{
			return packet[packetFilter].totalProfit;
}
double Talasnica::OrdersManager::averageOpenPrice(void)
{
	return 0;
}
double Talasnica::OrdersManager::averageOpenPrice(Talasnica::Type::PacketFilter packetFilter)
{
	if(packet[packetFilter].jmenovatel != 0) {
		return packet[packetFilter].citatel / packet[packetFilter].jmenovatel;
	}
	return 0;
}

int Talasnica::OrdersManager::getTicket(Talasnica::Type::PacketFilter packetFilter, unsigned int index){
	if(index > packet[packetFilter].orders.size()) {
		return 0;
	}
	return packet[packetFilter].orders[index]->ticket;
}
