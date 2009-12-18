#include "AverageOrder.h"

using namespace std;

namespace Talasnica
{

	AverageOrder::AverageOrder(void)
	{
	}

	AverageOrder::AverageOrder(string description)
	{
		//this->type = type;
		this->description = description;
	}

	AverageOrder::~AverageOrder(void)
	{
	}

	void AverageOrder::add(Order &order){
		cout << "AverageOrder " << description << endl << " add " << order << endl;
	}

}
