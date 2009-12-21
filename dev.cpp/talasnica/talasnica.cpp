//+------------------------------------------------------------------+
//|                                              Sample DLL for MQL4 |
//|                 Copyright © 2004-2006, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "talasnica.h"

using namespace std;

Talasnica::TradePacket g_tradePacket;

static int CompareMqlStr(const void *left,const void *right);
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
  {
//----
   switch(ul_reason_for_call)
     {
      case DLL_PROCESS_ATTACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
     }
//----
   return(TRUE);
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
		
		Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, (Talasnica::OperationType)type, lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
		
		cout << "order pred g_tradePacket.add(order); " << order << " on " << &order << endl;
		
		g_tradePacket.add(order);

		cout << "order po g_tradePacket.add(order); " << order << " on " << &order << endl;
		
		cout << "registrovano " << g_tradePacket.count() << " obchodu" << endl;
		
		return ticket;
  }

void __stdcall talasnica_sortOrders(void)
{
	g_tradePacket.sort();
}

void __stdcall talasnica_reset(void){
	g_tradePacket.reset();
}

char* __stdcall talasnica_getTradepacketInfo(void)
  {
		stringstream proud(ios_base::out);

		proud << g_tradePacket;
		//return (proud.str().c_str());
		string info = proud.str();
		//return(info.c_str());
		char *str;
		str = new char[info.length() + 1];
		strcpy(str, info.c_str());
		return str;
		
  }
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù dle druhu
   */
int __stdcall talasnica_count(int type)
{
	return g_tradePacket.count((Talasnica::OrdersGroup)type);
}
   /**
   * poèítadlo obchodù
   *
   * poèet lotù
   */
double __stdcall talasnica_volume(int type)
{
	return g_tradePacket.volume((Talasnica::OrdersGroup)type);
}
   /**
   * poèítadlo obchodù
   *
   * profit
   */
double __stdcall talasnica_profit(int type)
{
	return g_tradePacket.profit((Talasnica::OrdersGroup)type);
}
   /**
   * swap
   *
   */
double __stdcall talasnica_swap(int type)
{
	return g_tradePacket.swap((Talasnica::OrdersGroup)type);
}
   /**
   * profit + swap
   *
   */
double __stdcall talasnica_totalProfit(int type)
{
	return g_tradePacket.totalProfit((Talasnica::OrdersGroup)type);
}
   /**
   * aproximovaná vstupní cena
   *
   */
double __stdcall talasnica_averageOpenPrice(int type)
{
	return g_tradePacket.averageOpenPrice((Talasnica::OrdersGroup)type);
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int __stdcall GetIntValue(const int ipar)
  {
   printf("GetIntValue takes %d\n",ipar);
   return(ipar);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
double __stdcall GetDoubleValue(const double dpar)
  {
   printf("GetDoubleValue takes %.8lf\n",dpar);
   return(dpar);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
char* __stdcall GetStringValue(char *spar)
  {
   printf("GetDoubleValue takes \"%s\"\n",spar);
   return(spar);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
double __stdcall GetArrayItemValue(const double *arr,const int arraysize,const int nitem)
  {
//----
   if(arr==NULL)
     {
      printf("GetArrayItemValue: NULL array\n");
      return(0.0);
     }
   if(arraysize<=0)
     {
      printf("GetArrayItemValue: wrong arraysize (%d)\n", arraysize);
      return(0.0);
     }
   if(nitem<0 || nitem>=arraysize)
     {
      printf("GetArrayItemValue: wrong item number (%d)\n", nitem);
      return(0.0);
     }
//----
   return(arr[nitem]);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
 BOOL __stdcall SetArrayItemValue(double *arr,const int arraysize,const int nitem,const double value)
  {
//----
   if(arr==NULL)
     {
      printf("GetArrayItemValue: NULL array\n");
      return(FALSE);
     }
   if(arraysize<=0)
     {
      printf("GetArrayItemValue: wrong arraysize (%d)\n", arraysize);
      return(FALSE);
     }
   if(nitem<0 || nitem>=arraysize)
     {
      printf("GetArrayItemValue: wrong item number (%d)\n", nitem);
      return(FALSE);
     }
//----
   arr[nitem]=value;
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
 double __stdcall GetRatesItemValue(const RateInfo* rates,const int rates_total,const int shift,const int nrate)
  {
//----
   if(rates==NULL)
     {
      printf("GetRatesItemValue: NULL array\n");
      return(0.0);
     }
//----
   if(rates_total<0)
     {
      printf("GetRatesItemValue: wrong rates_total number (%d)\n", rates_total);
      return(0.0);
     }
//----
   if(shift<0 || shift>=rates_total)
     {
      printf("GetRatesItemValue: wrong shift number (%d)\n", shift);
      return(0.0);
     }
//----
   if(nrate<0 || nrate>5)
     {
      printf("GetRatesItemValue: wrong rate index (%d)\n", nrate);
      return(0.0);
     }
//----
   int nitem=rates_total-1-shift;
   switch(nrate)
     {
      case 0: return double(rates[nitem].ctm);
      case 1: return rates[nitem].open;
      case 2: return rates[nitem].low;
      case 3: return rates[nitem].high;
      case 4: return rates[nitem].close;
      case 5: return rates[nitem].vol;
     }
//----
   return(0.0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
 int __stdcall SortStringArray(MqlStr *arr,const int arraysize)
  {
//----
   if(arr==NULL)
     {
      printf("SortStringArray: NULL array\n");
      return(-1);
     }
   if(arraysize<=0)
     {
      printf("SortStringArray: wrong arraysize (%d)\n", arraysize);
      return(-1);
     }
//----
   qsort(arr,arraysize,sizeof(MqlStr),CompareMqlStr);
//----
   return(arraysize);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
 int __stdcall ProcessStringArray(MqlStr *arr,const int arraysize)
  {
   int   len1,len2;
//----
   if(arr==NULL)
     {
      printf("ProcessStringArray: NULL array\n");
      return(-1);
     }
   if(arraysize<=0)
     {
      printf("ProcessStringArray: wrong arraysize (%d)\n", arraysize);
      return(-1);
     }
//----
   for(int i=0; i<arraysize-1; i++)
     {
      if(arr[i].string==NULL) len1=0;
      else len1=strlen(arr[i].string);
      if(arr[i+1].string==NULL) len2=0;
      else len2=strlen(arr[i+1].string);
      //---- uninitialized string
      if(arr[i+1].string==NULL) continue;
      //---- destination string is uninitialized and cannot be allocated within dll
      if(arr[i].string==NULL)   continue;
      //---- memory piece is less than needed and cannot be reallocated within dll
      if(arr[i].len<len1+len2)  continue;
      //---- final processing
      strcat(arr[i].string,arr[i+1].string);
     }
//----
   return(arraysize);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int CompareMqlStr(const void *left,const void *right)
  {
   MqlStr *leftstr=(MqlStr *)left;
   MqlStr *rightstr=(MqlStr *)right;
//----
   if(leftstr->string==NULL) return(-1);
   if(rightstr->string==NULL) return(1);
//----
   return(strcmp(leftstr->string,rightstr->string));
  }
//+------------------------------------------------------------------+
