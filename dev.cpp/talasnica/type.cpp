#include "type.h"

Talasnica::Type::Order::Order(int type)
{
	value = type;
}

Talasnica::Type::Order::~Order(void)
{
}

std::map<const int, const std::string> Talasnica::Type::Order::names = Talasnica::Type::Order::initialize_names();
std::map<const int, const std::string> Talasnica::Type::Order::initialize_names(void)
 	{

		std::map<const int, const std::string> map;

		map.insert(std::make_pair(Talasnica::Type::Order::BUY,std::string("Buying position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELL,std::string("Selling position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::Order::SELLSTOP,std::string("Sell stop pending position.")));

		return map;
 	}
