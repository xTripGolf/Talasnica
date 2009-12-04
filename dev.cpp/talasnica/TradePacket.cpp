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
			zasobnik.insert(std::make_pair(order.getTicket(),order));

		//zasobnik.push(order); // Metoda push uloží prvek na vrchol zásobníku. 
		
  }

	void TradePacket::reset(void) {
		zasobnik.clear();
	}

	int TradePacket::count(int type) {
		return zasobnik.size();
	}

	string TradePacket::getInfo(void)
	{
		stringstream proud(ios_base::out);

		proud << "Poèet prvkù je " << count();
		return proud.str();
	}

}