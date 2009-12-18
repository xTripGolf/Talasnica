#pragma once
#include "Order.h"
//#include <stack>
#include <map>
#include<vector>
#include<algorithm>
#include<utility>
#include<functional>


namespace Talasnica
{

	class Order;

	const int OP_BUY = 0; //Buying position. 
	const int  OP_SELL = 1; //Selling position. 
	const int  OP_BUYLIMIT = 2; //Buy limit pending position. 
	const int  OP_SELLLIMIT = 3; //Sell limit pending position. 
	const int  OP_BUYSTOP = 4; //Buy stop pending position. 
	const int  OP_SELLSTOP = 5; //Sell stop pending position. 
	// extended positions type
	const int  OP_PROFIT = 6; // positions in profit
	const int  OP_LOSS = 7; // loss positions 
	const int  OP_OPENED = 8; // all opened positions
	const int  OP_PREMOC = 9; // nezamèené pozice

	class TradePacket
	{
		private:
			//
			std::map<int,Order> tradeList;
			std::map<int, std::vector<Order> > packet;

			public:
        TradePacket(void);
				~TradePacket(void);
        void add(Order&);
				void reset(void);
				int count();
				std::map<int, std::string> names;
		friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
  };
}