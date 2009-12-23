#include "OrdersManager.h"

using namespace std;

namespace Talasnica
{

	map<PacketFilter, const string> OrdersManager::descriptions = OrdersManager::initialize_descriptions();
 	map<PacketFilter, const string> OrdersManager::initialize_descriptions(void)
 	{

		map<PacketFilter, const string> map;

		map.insert(std::make_pair(BUY,std::string("Buying position.")));
		map.insert(std::make_pair(SELL,std::string("Selling position.")));
		map.insert(std::make_pair(BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(SELLSTOP,std::string("Sell stop pending position.")));
		map.insert(std::make_pair(PROFITED,std::string("Pozice v profitu.")));
		map.insert(std::make_pair(LOSSED,std::string("Pozice ve ztr�t�.")));
		map.insert(std::make_pair(ALL_OPENED,std::string("V�echny pozice.")));
		map.insert(std::make_pair(PREMOC,std::string("Nesp�rovan� pozice.")));

		return map;
 	}

	map<PacketFilter, const string> OrdersManager::names = OrdersManager::initialize_names();
 	map<PacketFilter, const string> OrdersManager::initialize_names(void)
 	{
		map<PacketFilter, const string> map;

		map.insert(std::make_pair(BUY,std::string("Buy")));
		map.insert(std::make_pair(SELL,std::string("Sell")));
		map.insert(std::make_pair(BUYLIMIT,std::string("Buy limit")));
		map.insert(std::make_pair(SELLLIMIT,std::string("Sell limit")));
		map.insert(std::make_pair(BUYSTOP,std::string("Buy stop")));
		map.insert(std::make_pair(SELLSTOP,std::string("Sell stop")));
		map.insert(std::make_pair(PROFITED,std::string("Profit")));
		map.insert(std::make_pair(LOSSED,std::string("Ztr�tov�")));
		map.insert(std::make_pair(ALL_OPENED,std::string("V�echny")));
		map.insert(std::make_pair(PREMOC,std::string("Nesp�rovan�")));

		return map;
 	}
}