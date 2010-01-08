#include "StdAfx.h"
#include "OrderManager.h"

using namespace std;

#ifdef _DEBUG
		//std::ofstream Talasnica::OrderManager::log("talasnica_OrderManager.log");
#endif

Talasnica::OrderManager::OrderManager(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::OrderManager::OrderManager(void)" << endl;
		log << "\tVytv���m objekt Talasnica::OrderManager." << endl;
	#endif
}

Talasnica::OrderManager::~OrderManager(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::OrderManager::~OrderManager(void)" << endl;
		log << "\tRu��m objekt Talasnica::OrderManager." << endl;
	#endif
}

void Talasnica::OrderManager::add(Order order)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "void Talasnica::orderManager::add(Order order)" << endl;
		log << "\tP�id�v�m obchod do Ordermanageru." << endl;
		log << order << endl;
	#endif
	
	ordersPool.insert(std::make_pair(order.ticket,order));
}

	/**

	**/
Talasnica::OrderManager::PacketMap Talasnica::OrderManager::initialize_packet(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::OrderManager::PacketMap Talasnica::OrderManager::initialize_packet(void)" << endl;
		log << "\tInicializuji packet" << endl;
		log << "\tpacket size" << packet.size() << endl;
	#endif
	
	Talasnica::Type::Packet packetType;

	// da li je u� paket inicializovan�
	if(packet.size() == packetType.size) {
		#ifdef _DEBUG
			log << "\tpacket u� byl inicializovan�, nic se d�lat nebude" << packet.size() << endl;
		#endif
		return packet;
	}
	
	// ako ne, inicializujeme ho
	//for(packetType = 0; packetType < packetType.size; packetType++) {
	for(int i = 0; i < packetType.size; i++) {
		packetType = i;
		packet.insert(std::make_pair(packetType,Talasnica::OrderPacket()));
	}

	#ifdef _DEBUG
		log << "\tpacket byl inicializov�n, packet size = " << packet.size() << endl;
	#endif

	return packet;
}

void Talasnica::OrderManager::sort(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "void Talasnica::OrderManager::sort(void)" << endl;
		log << "\tT��d�m packet" << endl;
		log << "\tpacket size" << packet.size() << endl;
	#endif

	try {
		initialize_packet();
	}
	catch(Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
	}

	// projdeme ordersPool nah�eme obchody do paket�
	Talasnica::OrderManager::OrdersPoolMap::iterator poolIterator;
	for(poolIterator = ordersPool.begin(); poolIterator != ordersPool.end(); poolIterator++) {
		Order & order = poolIterator->second;
		Talasnica::Type::Packet packetFilter(order.type);
		packet[packetFilter].add(order);

		if(order.totalProfit > 0) {
			packet[Talasnica::Type::Packet::PROFITED].add(order);
		}
		else {
			packet[Talasnica::Type::Packet::LOSSED].add(order);
		}
		
		if(order.type == Talasnica::Type::Order::BUY || order.type == Talasnica::Type::Order::SELL) {
			packet[Talasnica::Type::Packet::ALL_OPENED].add(order);
		}
	}


	// set��d�me pakety
	Talasnica::OrderManager::PacketMap::iterator packetIterator;
	for(packetIterator = packet.begin(); packetIterator != packet.end(); packetIterator++) {
		#ifdef _DEBUG
			log << "\tpacket *** " << packetIterator->first << " *** p�ed t��d�n�m " << endl << packetIterator->second << endl;
		#endif
		packetIterator->second.sort();
		#ifdef _DEBUG
			log << "\tpacket *** " << packetIterator->first << " *** po t��d�n� " << endl << packetIterator->second << endl;
		#endif
	}
}

void Talasnica::OrderManager::reset(void) {
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "void Talasnica::OrderManager::reset(void)" << endl;
		log << "\tresetuji ordermana�era" << endl;
	#endif	
	ordersPool.clear();
	packet.clear();
}

int Talasnica::OrderManager::count(void) {
	return ordersPool.size();
}

int Talasnica::OrderManager::count(Talasnica::Type::Packet packetFilter)
{
	return packet[packetFilter].count;
}
/*double Talasnica::OrderManager::volume(void)
{
	return 0;
}*/
double Talasnica::OrderManager::volume(Talasnica::Type::Packet packetFilter)
{
	return packet[packetFilter].volume;
}
/*double Talasnica::OrderManager::profit(void)
{
	return 0;
}*/
double Talasnica::OrderManager::profit(Talasnica::Type::Packet packetFilter)
{
	return packet[packetFilter].profit;
}
/*double Talasnica::OrderManager::swap(void)
{
	return 0;
}*/
double Talasnica::OrderManager::swap(Talasnica::Type::Packet packetFilter)
{
	return packet[packetFilter].swap;
}
/*double Talasnica::OrderManager::totalProfit(void)
{
	return 0;
}*/
double Talasnica::OrderManager::totalProfit(Talasnica::Type::Packet packetFilter)
{
			return packet[packetFilter].totalProfit;
}
/*double Talasnica::OrderManager::averageOpenPrice(void)
{
	return 0;
}*/
double Talasnica::OrderManager::averageOpenPrice(Talasnica::Type::Packet packetFilter)
{
	if(packet[packetFilter].jmenovatel != 0) {
		return packet[packetFilter].citatel / packet[packetFilter].jmenovatel;
	}
	return 0;
}

int Talasnica::OrderManager::getTicket(Talasnica::Type::Packet packetFilter, unsigned int index){
	if(index > packet[packetFilter].orders.size()) {
		return 0;
	}
	return packet[packetFilter].orders[index]->ticket;
}

