#include "StdAfx.h"
#include "Type.h"

using namespace std;

Talasnica::Type::Packet::Packet(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Packet::Packet(void)" << endl;
		log << "\t\t!!!!! neznámý typ packetu" << endl;
		log << "\tVytváøím objekt Talasnica::Type::Packet." << endl;
		log << "\tvalue = " << value << endl;
	#endif
	value = Talasnica::Type::Packet::UNDEFINED;
	#ifdef _DEBUG
		log << "\tvalue = " << value << endl;
	#endif
}

/*
Talasnica::Type::Packet::Packet(const Talasnica::Type::Packet& packet)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Packet::Packet(const Talasnica::Type::Packet& packet)" << endl;
		log << "\t\tkopírovací konstruktor" << endl;
		log << "\tVytváøím objekt Talasnica::Type::Packet." << endl;
		log << "\tvalue = " << value << endl;
	#endif
	value = packet.value;
	#ifdef _DEBUG
		log << "\tvalue = " << value << endl;
	#endif
}*/

Talasnica::Type::Packet::Packet(int type)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Packet::Packet(int i)" << endl;
		log << "\t\ttype = " << type << endl;
		log << "\tVytváøím objekt Talasnica::Type::Packet." << endl;
	#endif

		if(type >= size || type < 0) {
			throw new Talasnica::Exception::TypeOverFlow("Neplatný typ packetu.");
		}
		value = type;
}

Talasnica::Type::Packet::Packet(Talasnica::Type::Order& order)
{
	int type = order.value;

	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Packet::Packet(Talasnica::Type::Order& order)" << endl;
		log << "\t\ttype = " << type << endl;
		log << "\tVytváøím objekt Talasnica::Type::Packet." << endl;
	#endif

		if(type >= size || type < 0) {
			throw new Talasnica::Exception::TypeOverFlow("Neplatný typ packetu.");
		}
		value = type;
}

Talasnica::Type::Packet::~Packet(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Packet::~Packet(void)" << endl;
		log << "\tRuším objekt Talasnica::Type::Packet." << endl;
		log << "\tvalue = " << value << endl;
	#endif
}

std::map<int, const std::string> Talasnica::Type::Packet::names = Talasnica::Type::Packet::initialize_names();

std::map<int, const std::string> Talasnica::Type::Packet::initialize_names(void)
 	{

	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "std::map<int, const std::string> Talasnica::Type::Packet::initialize_names(void)" << endl;
	#endif

		std::map<int, const std::string> map;

		map.insert(std::make_pair(BUY,std::string("Buy")));
		map.insert(std::make_pair(SELL,std::string("Sell")));
		map.insert(std::make_pair(BUYLIMIT,std::string("Buy limit")));
		map.insert(std::make_pair(SELLLIMIT,std::string("Sell limit")));
		map.insert(std::make_pair(BUYSTOP,std::string("Buy stop")));
		map.insert(std::make_pair(SELLSTOP,std::string("Sell stop")));
		map.insert(std::make_pair(PROFITED,std::string("Profit")));
		map.insert(std::make_pair(LOSSED,std::string("Ztrátové")));
		map.insert(std::make_pair(ALL_OPENED,std::string("Všechny")));
		map.insert(std::make_pair(PREMOC,std::string("Nespárované")));

	#ifdef _DEBUG
		log << "\tStatická metoda vytvoøila jména." << endl;
		std::map<int, const std::string>::iterator it;
		for(it = map.begin(); it != map.end(); it++) {
			log << "#" << it->first << ": " << it->second << endl;
		}	
	#endif

		return map;
 	}


Talasnica::Type::Packet Talasnica::Type::Packet::operator++(int i) {
		
		if(value >= size) {
			throw Talasnica::Exception::TypeOverFlow("Packet type se dostává mimo povolený rozsah.");
		}

		//if(value < size()) {
			int newValue = value;
			newValue++;
		//}
		return Talasnica::Type::Packet(newValue);
	}

bool Talasnica::Type::Packet::operator<(int i) {
	if(value < i) {
		return true;
	}
	return false;
}
bool Talasnica::Type::Packet::operator<(const Talasnica::Type::Packet& packetType) const {
	if(value < packetType.value) {
		return true;
	}
	return false;
}
