#include "Order.h"
#include "AverageOrder.h"

using namespace std;

namespace Talasnica
{

	AverageOrder::AverageOrder(void)
	{
		cout << "AverageOrder::AverageOrder(void)" << endl;
	}

	AverageOrder::AverageOrder(string description)
	{
		cout << "AverageOrder::AverageOrder(string description)" << endl;
		//this->type = type;
		this->description = description;
	}

	AverageOrder::~AverageOrder(void)
	{
		cout << "AverageOrder::~AverageOrder(void)" << endl;
	}

	void AverageOrder::add(Order &order){
		cout << "void AverageOrder::add(Order &order)" << endl;
		cout << "AverageOrder " << description << endl << " add " << order << endl;
		//order.openPrice += 10;
		orders.push_back(&order);
	}

		ostream& operator<<(ostream &os, const AverageOrder &averageOrder)
	{

		os << endl << "---------------------" << endl << averageOrder.description << endl;
		
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
