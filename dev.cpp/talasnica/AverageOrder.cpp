#include "Order.h"
#include "AverageOrder.h"

using namespace std;

namespace Talasnica
{

	AverageOrder::AverageOrder(void)
	{
		cout << "AverageOrder::AverageOrder(void)" << endl;
		AverageOrder::AverageOrder(string("Unknown description"));
	}

	AverageOrder::AverageOrder(string description)
	{
		cout << "AverageOrder::AverageOrder(string description)" << endl;
		//this->type = type;
		this->description = description;
		citatel = 0;
		jmenovatel = 0;
		count = 0;
		volume = 0;
		profit = 0;
		swap = 0;
	}

	AverageOrder::~AverageOrder(void)
	{
		cout << "AverageOrder::~AverageOrder(void)" << endl;
	}

	void AverageOrder::add(Order &order){
		cout << "void AverageOrder::add(Order &order)" << endl;
		cout << "AverageOrder " << description << endl << " add " << order << endl;
		orders.push_back(&order);
		citatel += order.lots * order.openPrice;
		jmenovatel += order.lots;
		count ++;
		volume += order.lots;
		profit += order.profit;
		swap += order.swap;
	}

	ostream& operator<<(ostream &os, const AverageOrder &averageOrder)
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

	void AverageOrder::sort(void)
	{
		cout << "void AverageOrder::sort(void)" << endl;
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
