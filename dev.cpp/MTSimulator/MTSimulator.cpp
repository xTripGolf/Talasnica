// MTSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MTSimulator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "MTSimulator -- Talasnica tester" << endl;
	
	talasnica_reset();
	talasnica_addOrder(4316628, "GBPUSD", 1259050941, 1, 0.10000000, 1.65350000, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	talasnica_addOrder(4313321, "GBPUSD", 1259137924, 0, 0.10000000, 1.66620000, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);
	talasnica_addOrder(100, "GBPUSD", 100, 1, 0.10000000, 1.8, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	talasnica_addOrder(200, "GBPUSD", 200, 1, 0.10000000, 1.9, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);
	talasnica_addOrder(500, "GBPUSD", 500, 1, 0.10000000, 1.85, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	talasnica_addOrder(400, "GBPUSD", 400, 1, 0.10000000, 1.55, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);
	talasnica_sortOrders();
	
	for(int i = 0; i < 15; i++) {
		cout << "packet name " << i << " " << talasnica_packetName(i) << endl;
		cout << "count " << i << " " << talasnica_packetCount(i) << endl;
		cout << "volume " << i << " " << talasnica_packetVolume(i) << endl;
		cout << "totalProfit " << i << " " << talasnica_packetTotalProfit(i) << endl;
		cout << "----------------------------------" << endl;
	}
	
	//cout << "count 1: " << talasnica_packetCount(1) << endl;
	/*cout << "ukoncit program";
	int znak;
	cin >> znak;*/
	return 0;
}



