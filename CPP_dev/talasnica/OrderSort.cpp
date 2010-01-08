#include "StdAfx.h"
#include "OrderSort.h"

using namespace std;

bool Talasnica::Sort::ByOpenPrice::operator()(Talasnica::Order * o1, Talasnica::Order * o2) {
	return o1->openPrice < o2->openPrice;
}