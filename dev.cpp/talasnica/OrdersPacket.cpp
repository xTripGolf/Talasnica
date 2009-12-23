#include "Order.h"
#include "OrdersPacket.h"

using namespace std;

namespace Talasnica
{

	OrdersPacket::OrdersPacket(void)
	{
		cout << "OrdersPacket::OrdersPacket(void)" << endl;
		OrdersPacket::OrdersPacket(string("Unknown description"));
	}

	OrdersPacket::OrdersPacket(string description)
	{
		cout << "OrdersPacket::OrdersPacket(string description)" << endl;
		//this->type = type;
		this->description = description;
		citatel = 0;
		jmenovatel = 0;
		count = 0;
		volume = 0;
		profit = 0;
		swap = 0;
		totalProfit = 0;
	}

	OrdersPacket::~OrdersPacket(void)
	{
		cout << "OrdersPacket::~OrdersPacket(void)" << endl;
	}

	void OrdersPacket::add(Order &order){
		cout << "void OrdersPacket::add(Order &order)" << endl;
		cout << "OrdersPacket " << description << endl << " add " << order << endl;
		orders.push_back(&order);
		citatel += order.lots * order.openPrice;
		jmenovatel += order.lots;
		count ++;
		volume += order.lots;
		profit += order.profit;
		swap += order.swap;
		totalProfit += order.totalProfit;
	}

	ostream& operator<<(ostream &os, const OrdersPacket &averageOrder)
	{

		os << endl << "---------------------" << endl << averageOrder.description << endl;

		os << "count: " << averageOrder.count << endl;
		os << "volume: " << averageOrder.volume << endl;
		os << "profit: " << averageOrder.profit << endl;
		os << "swap: " << averageOrder.swap << endl;
		
		/*vector<Order *>::iterator ordersIterator;
		for(ordersIterator = averageOrder.orders.begin(); ordersIterator != averageOrder.orders.end(); ordersIterator++) {
				os << *(ordersIterator) << endl;
		}*/

		for(int i =0; i != averageOrder.orders.size(); i++) {
			os << *(averageOrder.orders[i]) << endl;
		}

		return os;
		
	}

	void OrdersPacket::sort(void)
	{
		cout << "void OrdersPacket::sort(void)" << endl;
		OrderSort sort;
		std::sort(orders.begin(),orders.end(),sort);
			cout << "serazeno podle ceny" << endl;
		for(unsigned int i = 0; i < orders.size(); i++){
			cout << orders[i] << endl;
		}
	}

	bool OrderSort::operator()(Order * o1, Order * o2) {
		cout << "bool OrderSort::operator()(Order * o1, Order * o2)" << endl;
		return o1->openPrice < o2->openPrice;
  }
}
