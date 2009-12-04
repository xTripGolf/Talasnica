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

		//zasobnik.push(order); // Metoda push uloží prvek na vrchol zásobníku. 
		
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

		proud << "Poèet prvkù je " << count();
		return proud.str();
	}*/

	ostream& operator<<(ostream &os, TradePacket &packet)
	{
		os << "*********** TALASNICA TRADE PACKET *********** " << endl;
		os << "Celkový poèet obchodù " << packet.count() << endl;
		os << " všechny obchody" << endl;
		return os;
	}
}