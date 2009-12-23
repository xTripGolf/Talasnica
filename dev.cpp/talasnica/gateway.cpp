//+------------------------------------------------------------------+
//|                                              Sample DLL for MQL4 |
//|                 Copyright © 2004-2006, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "gateway.h"

using namespace std;

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
	
		cout << "talasnica_addOrder() " << endl;
		
		try {
			Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, Talasnica::OrderType(type), lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
			g_ordersManager.add(order);
		}
		catch (Talasnica::Exception e) {
			return 0;
		}
		
		return ticket;
  }

void __stdcall talasnica_sortOrders(void)
{
	g_ordersManager.sort();
}

void __stdcall talasnica_reset(void){
	g_ordersManager.reset();
}

char* __stdcall talasnica_printOrdersManager(void)
  {
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
	return g_ordersManager.count(Talasnica::PacketFilter(packetFilter));
}
   /**
   * poèítadlo obchodù
   *
   * poèet lotù
   */
double __stdcall talasnica_packetVolume(int packetFilter)
{
	return g_ordersManager.volume(Talasnica::PacketFilter(packetFilter));
}
   /**
   * poèítadlo obchodù
   *
   * profit
   */
double __stdcall talasnica_packetProfit(int packetFilter)
{
	return g_ordersManager.profit(Talasnica::PacketFilter(packetFilter));
}
   /**
   * swap
   *
   */
double __stdcall talasnica_packetSwap(int packetFilter)
{
	return g_ordersManager.swap(Talasnica::PacketFilter(packetFilter));
}
   /**
   * profit + swap
   *
   */
double __stdcall talasnica_packetTotalProfit(int packetFilter)
{
	return g_ordersManager.totalProfit(Talasnica::PacketFilter(packetFilter));
}
   /**
   * aproximovaná vstupní cena
   *
   */
double __stdcall talasnica_packetOpenPrice(int packetFilter)
{
	return g_ordersManager.averageOpenPrice(Talasnica::PacketFilter(packetFilter));
}
   /**
   * vybere obchod
   *
   */
int __stdcall talasnica_getTicket(int packetFilter, int index)
{
	return g_ordersManager.getTicket(Talasnica::PacketFilter(packetFilter), index);
}

   /**
   * vrátí název paketu obchodù
   *
   */
char* __stdcall talasnica_packetName(int packetFilter){
	string name = g_ordersManager.getPacketName(Talasnica::PacketFilter(packetFilter));
	return string2char(name);
}
   /**
   * vrátí popis paketu obchodù
   *
   */
char* __stdcall talasnica_packetDescription(int packetFilter){
	string desc = g_ordersManager.getPacketDescription(Talasnica::PacketFilter(packetFilter));
	return string2char(desc);
}
