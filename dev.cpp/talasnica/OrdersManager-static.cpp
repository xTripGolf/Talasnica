#include "OrdersManager.h"

using namespace std;

namespace Talasnica
{

	map<Talasnica::Type::PacketFilter, const string> OrdersManager::descriptions = OrdersManager::initialize_descriptions();
 	map<Talasnica::Type::PacketFilter, const string> OrdersManager::initialize_descriptions(void)
 	{

		map<Talasnica::Type::PacketFilter, const string> map;

		map.insert(std::make_pair(Talasnica::Type::BUY,std::string("Buying position.")));
		map.insert(std::make_pair(Talasnica::Type::SELL,std::string("Selling position.")));
		map.insert(std::make_pair(Talasnica::Type::BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(Talasnica::Type::BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::SELLSTOP,std::string("Sell stop pending position.")));
		map.insert(std::make_pair(Talasnica::Type::PROFITED,std::string("Pozice v profitu.")));
		map.insert(std::make_pair(Talasnica::Type::LOSSED,std::string("Pozice ve ztrátì.")));
		map.insert(std::make_pair(Talasnica::Type::ALL_OPENED,std::string("Všechny pozice.")));
		map.insert(std::make_pair(Talasnica::Type::PREMOC,std::string("Nespárované pozice.")));

		return map;
 	}

	map<Talasnica::Type::PacketFilter, const string> OrdersManager::names = OrdersManager::initialize_names();
 	map<Talasnica::Type::PacketFilter, const string> OrdersManager::initialize_names(void)
 	{
		map<Talasnica::Type::PacketFilter, const string> map;

		map.insert(std::make_pair(Talasnica::Type::BUY,std::string("Buy")));
		map.insert(std::make_pair(Talasnica::Type::SELL,std::string("Sell")));
		map.insert(std::make_pair(Talasnica::Type::BUYLIMIT,std::string("Buy limit")));
		map.insert(std::make_pair(Talasnica::Type::SELLLIMIT,std::string("Sell limit")));
		map.insert(std::make_pair(Talasnica::Type::BUYSTOP,std::string("Buy stop")));
		map.insert(std::make_pair(Talasnica::Type::SELLSTOP,std::string("Sell stop")));
		map.insert(std::make_pair(Talasnica::Type::PROFITED,std::string("Profit")));
		map.insert(std::make_pair(Talasnica::Type::LOSSED,std::string("Ztrátové")));
		map.insert(std::make_pair(Talasnica::Type::ALL_OPENED,std::string("Všechny")));
		map.insert(std::make_pair(Talasnica::Type::PREMOC,std::string("Nespárované")));

		return map;
 	}
}