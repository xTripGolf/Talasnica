//+------------------------------------------------------------------+
//|                                              Sample DLL for MQL4 |
//|                 Copyright © 2004-2006, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "gateway.h"

using namespace std;

std::ofstream log("talasnica.log");
std::ofstream errLog("talasnica-err.log");
Talasnica::OrdersManager g_ordersManager;

char * string2char(string s){
	
	int lenght = s.length() + 1;
	char *ch;
	ch = new char[lenght];
	strcpy_s(ch, lenght, s.c_str());
	return ch;
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int __stdcall talasnica_addOrder(const int ticket,
											const char *symbol,
											const int openTime,
											const int type,
											const double lots,
											const double openPrice,
											const double stopLoss,
											const double takeProfit,
											const int expiration,
											const int closeTime,
											const double closePrice,
											const double commission,
											const double profit,
											const double swap,
											const char *comment,
											const int magicNumber)
  {
	
		log << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log.width(80);
		log.fill('-');
		log << "" << endl;
		log << "\tint __stdcall talasnica_addOrder(param orders)" << endl;
		log << "\t\tticket=" << ticket << endl;
		log << "\t\tsymbol=" << symbol << endl;
		log << "\t\topenTime=" << openTime << endl;
		log << "\t\ttype=" << type << endl;
		log << "\t\tlots=" << lots << endl;
		log << "\t\topenPrice=" << openPrice << endl;
		log << "\t\tstopLoss=" << stopLoss << endl;
		log << "\t\ttakeProfit=" << takeProfit << endl;
		log << "\t\texpiration=" << expiration << endl;
		log << "\t\tcloseTime=" << closeTime << endl;
		log << "\t\tclosePrice=" << closePrice << endl;
		log << "\t\tcommission=" << commission << endl;
		log << "\t\tprofit=" << profit << endl;
		log << "\t\tswap=" << swap << endl;
		log << "\t\tcomment=" << comment << endl;
		log << "\t\tmagicNumber=" << magicNumber << endl;


		//cout << "talasnica_addOrder() " << endl;
		
		try {
			Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, Talasnica::Type::Order(type), lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
			g_ordersManager.add(order);
		}
		catch (Talasnica::Exception::EnumOverFlow e) {
			errLog << e << endl;
			return 0;
		}
		
		return ticket;
  }

void __stdcall talasnica_sortOrders(void)
{
	log << "\tvoid __stdcall talasnica_sortOrders(void)" << endl;
	try {
		g_ordersManager.sort();
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
	}
}

void __stdcall talasnica_reset(void){
	log << "\tvoid __stdcall talasnica_reset(void)" << endl;
	try {
		g_ordersManager.reset();
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
	}
}

char* __stdcall talasnica_printOrdersManager(void)
  {
		log << "\tchar* __stdcall talasnica_printOrdersManager(void)" << endl;
		stringstream proud(ios_base::out);

		proud << g_ordersManager;
		//return (proud.str().c_str());
		return string2char(proud.str());
		
  }
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù dle druhu
   */
int __stdcall talasnica_packetCount(int packetFilter)
{
	log << "\tint __stdcall talasnica_packetCount(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.count(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0;
	}
}
   /**
   * poèítadlo obchodù
   *
   * poèet lotù
   */
double __stdcall talasnica_packetVolume(int packetFilter)
{
	log << "\tdouble __stdcall talasnica_packetVolume(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.volume(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0.0;
	}
}
   /**
   * poèítadlo obchodù
   *
   * profit
   */
double __stdcall talasnica_packetProfit(int packetFilter)
{
	log << "\tdouble __stdcall talasnica_packetProfit(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.profit(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0.0;
	}
}
   /**
   * swap
   *
   */
double __stdcall talasnica_packetSwap(int packetFilter)
{
	log << "\tdouble __stdcall talasnica_packetSwap(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.swap(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0.0;
	}
}
   /**
   * profit + swap
   *
   */
double __stdcall talasnica_packetTotalProfit(int packetFilter)
{
	log << "\tdouble __stdcall talasnica_packetTotalProfit(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.totalProfit(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0.0;
	}
}
   /**
   * aproximovaná vstupní cena
   *
   */
double __stdcall talasnica_packetOpenPrice(int packetFilter)
{
	log << "\tdouble __stdcall talasnica_packetOpenPrice(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		return g_ordersManager.averageOpenPrice(Talasnica::Type::PacketFilter(packetFilter));
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0.0;
	}
}
   /**
   * vybere obchod
   *
   */
int __stdcall talasnica_getTicket(int packetFilter, int index)
{
	log << "\tint __stdcall talasnica_getTicket(int packetFilter, int index)" << endl;
	log << "\t\tpacketFilter=" << packetFilter<< "\t\tindex=" << index << endl;
	try {
		return g_ordersManager.getTicket(Talasnica::Type::PacketFilter(packetFilter), index);
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return 0;
	}
}

   /**
   * vrátí název paketu obchodù
   *
   */
char* __stdcall talasnica_packetName(int packetFilter){
	log << "\tchar* __stdcall talasnica_packetName(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		//string name = g_ordersManager.getPacketName(Talasnica::Type::PacketFilter(packetFilter));
		string name = Talasnica::Type::PacketFilter.names[packetFilter];
		return string2char(name);
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return "Error name";
	}
}
   /**
   * vrátí popis paketu obchodù
   *
   */
char* __stdcall talasnica_packetDescription(int packetFilter){
	log << "\tchar* __stdcall talasnica_packetDescription(int packetFilter)" << endl;
	log << "\t\tpacketFilter=" << packetFilter << endl;
	try {
		//string desc = g_ordersManager.getPacketDescription(Talasnica::Type::PacketFilter(packetFilter));
		string desc = Talasnica::Type::PacketFilter.descriptions[packetFilter];
		return string2char(desc);
	}
	catch (Talasnica::Exception::EnumOverFlow e) {
		errLog << e << endl;
		return "Error description";
	}
}
