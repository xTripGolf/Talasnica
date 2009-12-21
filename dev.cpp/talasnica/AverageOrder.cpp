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
		orders.push_back(&order);
	}

		ostream& operator<<(ostream &os, const AverageOrder &averageOrder)
	{

		os << endl << "---------------------" << endl << averageOrder.description << endl;
		
		vector<Order *>::iterator ordersIterator;
//		for(ordersIterator = averageOrder.orders.begin(); ordersIterator != averageOrder.orders.end(); ordersIterator++) {
				//os << *(ordersIterator) << endl;
	//	}

		return os;
		
	}

}
