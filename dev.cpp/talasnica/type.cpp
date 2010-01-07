#include "type.h"

using namespace std;

Talasnica::Type::Order::Order()
{
	value = Talasnica::Type::Order::UNDEFINED;
}

Talasnica::Type::Order::Order(int type)
{
	value = type;
}

Talasnica::Type::Order::~Order(void)
{
}

std::map<int, const std::string> Talasnica::Type::Order::names = Talasnica::Type::Order::initialize_names();
std::map<int, const std::string> Talasnica::Type::Order::initialize_names(void)
 	{

		std::map<int, const std::string> map;

		map.insert(std::make_pair(Talasnica::Type::Order::BUY,std::string("Buying position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELL,std::string("Selling position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELLSTOP,std::string("Sell stop pending position.")));

		return map;
 	}

int Talasnica::Type::Order::reverse() {
   switch (this->value) {
		case Talasnica::Type::Order::BUY:
    case Talasnica::Type::Order::BUYLIMIT:
    case Talasnica::Type::Order::BUYSTOP:
			return 1;
    case Talasnica::Type::Order::SELL:
    case Talasnica::Type::Order::SELLLIMIT:
    case Talasnica::Type::Order::SELLSTOP:
			return -1;
    default:
			throw Talasnica::Exception::EnumOverFlow("Neplatný typ obchodu."); 
   }
}

Talasnica::Type::PacketFilter::PacketFilter(int type)
{
	value = type;
}

Talasnica::Type::PacketFilter::PacketFilter(Talasnica::Type::Order orderType)
{
}

Talasnica::Type::PacketFilter::~PacketFilter(void)
{
}

int Talasnica::Type::PacketFilter::size(void)
{
	return 10;
}

int Talasnica::Type::PacketFilter::begin(void)
{
	return 0;
}

int Talasnica::Type::PacketFilter::end(void)
{
	return 10;
}

std::map<int, const std::string> Talasnica::Type::PacketFilter::descriptions = Talasnica::Type::PacketFilter::initialize_descriptions();
std::map<int, const std::string> Talasnica::Type::PacketFilter::initialize_descriptions(void)
 	{

		std::map<int, const std::string> map;

		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUY,std::string("Buying position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELL,std::string("Selling position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELLSTOP,std::string("Sell stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::PROFITED,std::string("Pozice v profitu.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::LOSSED,std::string("Pozice ve ztrátì.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::ALL_OPENED,std::string("Všechny pozice.")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::PREMOC,std::string("Nespárované pozice.")));

		return map;
 	}

std::map<int, const std::string> Talasnica::Type::PacketFilter::names = Talasnica::Type::PacketFilter::initialize_names();
 std::map<int, const std::string> Talasnica::Type::PacketFilter::initialize_names(void)
 	{
		std::map<int, const std::string> map;

		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUY,std::string("Buy")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELL,std::string("Sell")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUYLIMIT,std::string("Buy limit")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELLLIMIT,std::string("Sell limit")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::BUYSTOP,std::string("Buy stop")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::SELLSTOP,std::string("Sell stop")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::PROFITED,std::string("Profit")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::LOSSED,std::string("Ztrátové")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::ALL_OPENED,std::string("Všechny")));
		map.insert(std::make_pair(Talasnica::Type::PacketFilter::PREMOC,std::string("Nespárované")));
		return map;
 	}

 Talasnica::Type::PacketFilter Talasnica::Type::PacketFilter::operator++(int i) {
		cout << "PacketFilterEnum operator++(int i) - " << i << endl;
		if(this->value >= this->size()) {
			throw Talasnica::Exception::EnumOverFlow("PacketFilterEnum se dostává mimo povolený rozsah.");
		}

		//if(this->value < this->size()) {
			this->value++;
		//}
		return *this;
	}

	bool Talasnica::Type::Order::operator==(int i) {
		if(this->value == i) {
			return true;
		}
		return false;
	}

	bool Talasnica::Type::PacketFilter::operator<(int i) {
		if(this->value < i) {
			return true;
		}
		return false;
	}

	bool Talasnica::Type::PacketFilter::operator<(Talasnica::Type::PacketFilter packetFilter) {
		if(this->value < packetFilter.value) {
			return true;
		}
		return false;
	}

string Talasnica::Type::PacketFilter::getName(){
	return Talasnica::Type::PacketFilter.names[value];
	//return Talasnica::OrdersManager::names[packetFilter];
}
string Talasnica::Type::PacketFilter::getDescription(){
	return Talasnica::Type::PacketFilter.descriptions[value];
	//return Talasnica::OrdersManager::descriptions[packetFilter];
}