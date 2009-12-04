#include "TradePacket.h"

#include <stdexcept>

using namespace std;

namespace Talasnica
{
	TradePacket::TradePacket(void)
	{
	}

	TradePacket::~TradePacket(void)
	{
	}

  void TradePacket::add(Order order)
  {
		tradeList.insert(std::make_pair(order.ticket,order));
		packet[order.type].push_back(order);

		int index;
		if(order.totalProfit > 0) {
			index = OP_PROFIT;
		}
		else {
			index = OP_LOSS;
		}
		packet[index].push_back(order);
		
		if(order.type == OP_BUY && order.type == OP_SELL) {
			packet[OP_OPENED].push_back(order);
		}

		//zasobnik.push(order); // Metoda push ulo�� prvek na vrchol z�sobn�ku. 
		
  }

	void TradePacket::reset(void) {
		tradeList.clear();
		packet.clear();
	}

	int TradePacket::count() {
		return tradeList.size();
	}

	/*string TradePacket::getInfo(void)
	{
		stringstream proud(ios_base::out);

		proud << "Po�et prvk� je " << count();
		return proud.str();
	}*/

	ostream& operator<<(ostream &os, TradePacket &packet)
	{
		os << "*********** TALASNICA TRADE PACKET *********** " << endl;
		os << "Celkov� po�et obchod� " << packet.count() << endl;
		os << " v�echny obchody" << endl;
		return os;
	}
}