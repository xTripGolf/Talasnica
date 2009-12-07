#pragma once
#include "Order.h"
//#include <stack>
#include <map>
#include<vector>
#include<algorithm>
#include<utility>
#include<functional>

#define OP_BUY 0 //Buying position. 
#define OP_SELL 1 //Selling position. 
#define OP_BUYLIMIT 2 //Buy limit pending position. 
#define OP_SELLLIMIT 3 //Sell limit pending position. 
#define OP_BUYSTOP 4 //Buy stop pending position. 
#define OP_SELLSTOP 5 //Sell stop pending position. 
// extended positions type
#define OP_PROFIT 6 // positions in profit
#define OP_LOSS 7 // loss positions 
#define OP_OPENED 8 // all opened positions
#define OP_PREMOC 9 // nezamèené pozice

using namespace std;

namespace Talasnica
{

	class Order;

	class TradePacket
	{
		private:
			//
			map<int,Order> tradeList;
			map<int, vector<Order> > packet;
			public:
        TradePacket(void);
				~TradePacket(void);
        void add(Order);
				void reset(void);
				int count();
				//string getInfo(void);
		friend ostream& operator<<(ostream &os, TradePacket &objekt);
  };
}