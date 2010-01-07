#pragma once

#include <map>
#include <string>
#include "talasnica.h"

namespace Talasnica
{

	/*class Order;
	class OrdersManager;
	class OrdersPacket;

	namespace Sort {
		class ByOpenPrice;
	}*/

	namespace Type {
		class Order {
			private:
				int	value;
				static std::map<int, const std::string> initialize_names(void);
			public:
				Order();
				Order(int);
				~Order(void);
				static const int UNDEFINED = -1;
				static const int BUY = 0;
				static const int SELL = 1;
				static const int BUYLIMIT = 2;
				static const int SELLLIMIT = 3;
				static const int BUYSTOP = 4;
				static const int SELLSTOP = 5;
				static std::map<int, const std::string> names;
				bool operator==(int i);
		/**
		* vrací 1 pro long pozice a -1 pro short pozice
		**/
				int Talasnica::Type::Order::reverse();
			friend std::ostream& operator<<(std::ostream &os, const Talasnica::Type::Order &orderType);
		};

		class PacketFilter {
			private:
				int	value;
				static std::map<int, const std::string>  initialize_names(void);
				static std::map<int, const std::string>  initialize_descriptions(void);
			public:
				PacketFilter(int);
				PacketFilter(Talasnica::Type::Order);
				~PacketFilter(void);
				static const int UNDEFINED = -1;
				static const int BUY = 0;
				static const int SELL = 1;
				static const int BUYLIMIT = 2;
				static const int SELLLIMIT = 3;
				static const int BUYSTOP = 4;
				static const int SELLSTOP = 5;
				static const int PROFITED = 6;
				static const int LOSSED = 7;
				static const int ALL_OPENED = 8;
				static const int PREMOC = 9;

				/*static*/ int size(void);
				/*static*/ int begin(void);
				/*static*/ int end(void);
				static std::map<int, const std::string> names;
				static std::map<int, const std::string> descriptions;

				bool operator<(int i);
				bool operator<(Talasnica::Type::PacketFilter);
				Talasnica::Type::PacketFilter operator++(int);

				std::string getName(void);
				std::string getDescription(void);
			friend std::ostream& operator<<(std::ostream &os, const Talasnica::Type::PacketFilter &packetFilter);
		};
	}
}

Talasnica::Type::PacketFilter operator++(Talasnica::Type::PacketFilter& c, int);