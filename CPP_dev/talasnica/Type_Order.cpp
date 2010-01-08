#include "StdAfx.h"
#include "Type.h"

using namespace std;

Talasnica::Type::Order::Order(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Order::Order(void)" << endl;
		log << "\t\t!!!!! nezn�m� typ obchodu" << endl;
		log << "\tVytv���m objekt Talasnica::Type::Order." << endl;
		log << "\tvalue = " << value << endl;
	#endif
	value = Talasnica::Type::Order::UNDEFINED;
	#ifdef _DEBUG
		log << "\tvalue = " << value << endl;
	#endif
}
/*
Talasnica::Type::Order::Order(const Talasnica::Type::Order& order)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Order::Order(const Talasnica::Type::Order& order)" << endl;
		log << "\t\tkop�rovac� konstruktor" << endl;
		log << "\tVytv���m objekt Talasnica::Type::Order." << endl;
		log << "\tvalue = " << value << endl;
	#endif
	value = order.value;
	#ifdef _DEBUG
		log << "\tvalue = " << value << endl;
	#endif
}*/

Talasnica::Type::Order::Order(int type)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Order::Order(int i)" << endl;
		log << "\t\ttype = " << type << endl;
		log << "\tVytv���m objekt Talasnica::Type::Order." << endl;
	#endif

		if(type >= size || type < 0) {
			throw new Talasnica::Exception::TypeOverFlow("Neplatn� typ obchodu.");
		}
		value = type;
}

Talasnica::Type::Order::~Order(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "Talasnica::Type::Order::~Order(void)" << endl;
		log << "\tRu��m objekt Talasnica::Type::Order." << endl;
		log << "\tvalue = " << value << endl;
	#endif
}

std::map<int, const std::string> Talasnica::Type::Order::names = Talasnica::Type::Order::initialize_names();

std::map<int, const std::string> Talasnica::Type::Order::initialize_names(void)
 	{

	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "std::map<int, const std::string> Talasnica::Type::Order::initialize_names(void)" << endl;
	#endif

		std::map<int, const std::string> map;

		map.insert(std::make_pair(BUY,std::string("Buying position.")));
		map.insert(std::make_pair(SELL,std::string("Selling position.")));
		map.insert(std::make_pair(BUYLIMIT,std::string("Buy limit pending position.")));
		map.insert(std::make_pair(SELLLIMIT,std::string("Sell limit pending position.")));
		map.insert(std::make_pair(BUYSTOP,std::string("Buy stop pending position.")));
		map.insert(std::make_pair(SELLSTOP,std::string("Sell stop pending position.")));

	#ifdef _DEBUG
		log << "\tStatick� metoda vytvo�ila jm�na." << endl;
		std::map<int, const std::string>::iterator it;
		for(it = map.begin(); it != map.end(); it++) {
			log << "#" << it->first << ": " << it->second << endl;
		}	
	#endif

		return map;
 	}


int Talasnica::Type::Order::reverse() {
   switch (value) {
		case BUY:
    case BUYLIMIT:
    case BUYSTOP:
			return 1;
    case SELL:
    case SELLLIMIT:
    case SELLSTOP:
			return -1;
    default:
			throw Talasnica::Exception::TypeOverFlow("Neplatn� typ obchodu."); 
   }
}

double Talasnica::Type::Order::reverse(double lots) {

	int reverse = this->reverse();
	
	// normalizujeme loty, kdyby u� byly jednou reversov�ny
	if(lots < 0) {
		lots = -1 * lots;
	}

	return lots * reverse;
   
}

bool Talasnica::Type::Order::operator==(int i) {
	if(this->value == i) {
		return true;
	}
	return false;
}