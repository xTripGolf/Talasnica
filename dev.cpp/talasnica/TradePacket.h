#pragma once
#include "Order.h"
#include "AverageOrder.h"
#include <map>
//#include<vector>
#include<algorithm>
#include<utility>
#include<functional>


namespace Talasnica
{

	class Order;
	class AverageOrder;

	class TradePacket
	{
		private:
			//
			std::map<int,Order> tradeList;
			std::map<int, AverageOrder> packet;
			std::map<int, AverageOrder> initialize_packet();
			static std::map<int, const std::string> descriptions;
			static std::map<int, const std::string> initialize_descriptions(void);
		public:
				static const int OP_BUY; //Buying position. 
				static const int  OP_SELL; //Selling position. 
				static const int  OP_BUYLIMIT; //Buy limit pending position. 
				static const int  OP_SELLLIMIT; //Sell limit pending position. 
				static const int  OP_BUYSTOP; //Buy stop pending position. 
				static const int  OP_SELLSTOP; //Sell stop pending position. 
				// extended positions type
				static const int  OP_PROFIT; // positions in profit
				static const int  OP_LOSS; // loss positions 
				static const int  OP_OPENED; // all opened positions
				static const int  OP_PREMOC; // nezamèené pozice
			public:
        TradePacket(void);
				~TradePacket(void);
        void add(Order&);
				void reset(void);
				int count();
		friend std::ostream& operator<<(std::ostream &os, TradePacket &objekt);
  };

}