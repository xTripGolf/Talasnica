#pragma once

#include <map>

namespace Talasnica {

	namespace Type {
		class Type {
			protected:
				int	value;
			public:
		//friend std::ostream& operator<<(std::ostream &os, const Talasnica::Type::Type &type);
		};


		class Order : public Type
		{
			private:
				static std::map<int, const std::string> initialize_names(void);
			public:
				Order(void);
				//Order(const Talasnica::Type::Order& order);
				Order(int);
				~Order(void);
				static const int UNDEFINED = -1;
				static const int BUY = 0;
				static const int SELL = 1;
				static const int BUYLIMIT = 2;
				static const int SELLLIMIT = 3;
				static const int BUYSTOP = 4;
				static const int SELLSTOP = 5;
				static const int size = 6;
				static std::map<int, const std::string> names;
				bool operator==(int i);
					/**
					* vrací 1 pro long pozice a -1 pro short pozice
					**/
				int reverse();
				/**
				* vrací poèet lotù záporné nebo kladné podle typu obchodu short - /long +
				**/
				double reverse(double lots);
			friend std::ostream& operator<<(std::ostream &os, const Talasnica::Type::Order &orderType);
			friend class Packet;
		};

		class Packet : public Type {
			private:
				static std::map<int, const std::string> initialize_names(void);
		public:
				Packet(void);
				//Packet(const Talasnica::Type::Packet& packetType);
				Packet(int);
				Packet(Talasnica::Type::Order&);
				~Packet(void);			
				
				
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
				static const int size = 10;
				static std::map<int, const std::string> names;

				bool operator<(int i);
				bool operator<(const Talasnica::Type::Packet& packetType) const;
				Talasnica::Type::Packet operator++(int);

		friend std::ostream& operator<<(std::ostream &os, const Talasnica::Type::Packet &packetType);

		};

	}
}

