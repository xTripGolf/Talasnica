// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

using namespace std;

#ifdef _DEBUG
    std::ofstream log("talasnica.log");
#endif

Talasnica::OrderManager g_orderManager;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

char * string2char(string s){
	
	int lenght = s.length() + 1;
	char *ch;
	ch = new char[lenght];
	strcpy_s(ch, lenght, s.c_str());
	return ch;
}

/**
* Pøidá obchod do seznamu
*/
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
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "int __stdcall talasnica_addOrder(... hafo parametrù ...)" << endl;
		log.width(80);
		log.fill('-');
		log << "" << endl;
		log.fill(' ');
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
	#endif

	#ifdef _DEBUG
		/*log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "\tJména typu." << endl;
		std::map<int, const std::string>::iterator it;
		for(it = orderType.names.begin(); it != orderType.names.end(); it++) {
			log << "#" << it->first << ": " << it->second << endl;
		}*/
	#endif
	try {
			Talasnica::Type::Order orderType(type);
			Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, orderType, lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
			g_orderManager.add(order);
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
	//catch (Talasnica::Exception::Exception e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
			return 0;
	}

	return ticket;
}

/**
* Vyèistí seznam obchodù
*/

void __stdcall talasnica_reset(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "void __stdcall talasnica_reset(void)" << endl;
		log << "g_orderManager pøed smazáním:" << endl;
		log << g_orderManager << endl;
	#endif

	try {
		g_orderManager.reset();
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
	}
}

void __stdcall talasnica_sortOrders(void)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "void __stdcall talasnica_sortOrders(void)" << endl;
		log << "g_orderManager pøed tøídìním:" << endl;
		log << g_orderManager << endl;
	#endif
	try {
		g_orderManager.sort();
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
	}
}

/*char* __stdcall talasnica_printOrderManager(void)
  {
		
		stringstream proud(ios_base::out);

		proud << g_orderManager;
		//return (proud.str().c_str());
		return string2char(proud.str());
		
  }*/
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù dle druhu
   */
int __stdcall talasnica_packetCount(int packetFilter)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "int __stdcall talasnica_packetCount(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif

	try {
		return g_orderManager.count(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
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
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "double __stdcall talasnica_packetVolume(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	
	try {
		return g_orderManager.volume(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
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
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "double __stdcall talasnica_packetProfit(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	try {
		return g_orderManager.profit(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return 0.0;
	}
}
   /**
   * swap
   *
   */
double __stdcall talasnica_packetSwap(int packetFilter)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "double __stdcall talasnica_packetSwap(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	try {
		return g_orderManager.swap(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return 0.0;
	}
}
   /**
   * profit + swap
   *
   */
double __stdcall talasnica_packetTotalProfit(int packetFilter)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "double __stdcall talasnica_packetTotalProfit(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	try {
		return g_orderManager.totalProfit(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return 0.0;
	}
}
   /**
   * aproximovaná vstupní cena
   *
   */
double __stdcall talasnica_packetOpenPrice(int packetFilter)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "double __stdcall talasnica_packetOpenPrice(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	try {
		return g_orderManager.averageOpenPrice(Talasnica::Type::Packet(packetFilter));
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return 0.0;
	}
}
   /**
   * vybere obchod
   *
   */
int __stdcall talasnica_getTicket(int packetFilter, int index)
{
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "int __stdcall talasnica_getTicket(int packetFilter, int index)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
		log << "\t\tindex=" << index << endl;
	#endif
	try {
		return g_orderManager.getTicket(Talasnica::Type::Packet(packetFilter), index);
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return 0;
	}
}

   /**
   * vrátí název paketu obchodù
   *
   */
char* __stdcall talasnica_packetName(int packetFilter){
	#ifdef _DEBUG
		log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
		log << "char* __stdcall talasnica_packetName(int packetFilter)" << endl;
		log << "\t\tpacketFilter=" << packetFilter << endl;
	#endif
	try {
		//string name = g_orderManager.getPacketName(Talasnica::Type::PacketFilter(packetFilter));
		Talasnica::Type::Packet packetType;
		string name = packetType.names[packetFilter];
		return string2char(name);
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return "Error name";
	}
}
   /**
   * vrátí popis paketu obchodù
   *
   */
/*char* __stdcall talasnica_packetDescription(int packetFilter){
	
	try {
		//string desc = g_orderManager.getPacketDescription(Talasnica::Type::PacketFilter(packetFilter));
		string desc = Talasnica::Type::PacketFilter.descriptions[packetFilter];
		return string2char(desc);
	}
	catch (Talasnica::Exception::TypeOverFlow e) {
		cerr << e << endl;
		#ifdef _DEBUG
			log << endl << __DATE__ << " " << __TIME__ << " " << __FILE__ << endl;
			log << "\t*****ERROR*****" << endl;
			log << e << endl;
		#endif
		return "Error description";
	}
}*/


