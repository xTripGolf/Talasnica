// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	#ifdef _DEBUG
    wcout << "Test Talasnica - dll library for Metatrader" << endl;
	#endif

	talasnica_reset();

	talasnica_addOrder(4316628, "GBPUSD", 1259050941, 1, 0.10000000, 1.65350000, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	talasnica_addOrder(4313321, "GBPUSD", 1259137924, 0, 0.10000000, 1.66620000, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);
	talasnica_sortOrders();
	return 0;
}

