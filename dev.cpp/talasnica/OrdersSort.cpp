#include "OrdersSort.h"

	using namespace std;

	bool Talasnica::Sort::ByOpenPrice::operator()(Talasnica::Order * o1, Talasnica::Order * o2) {
		cout << "Talasnica::Sort::ByOpenPrice::operator()(Talasnica::Order * o1, Talasnica::Order * o2)" << endl;
		return o1->openPrice < o2->openPrice;
  }
