//+------------------------------------------------------------------+
//|                                              Sample DLL for MQL4 |
//|                 Copyright © 2004-2006, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "talasnica.h"

using namespace std;

Talasnica::TradePacket tradePacket;

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
	//printf("Registrován obchod %d\n",ticket);
	cout << "Registruji obchod " << endl;
	//Order *order = new Order();
	Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, (unsigned short)type, lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
	cout << order << endl;
	tradePacket.add(order);
	cout << "registrovano " << tradePacket.count() << " obchodu" << endl;
	return ticket;
  }

void __stdcall talasnica_reset(void){
	tradePacket.reset();
}

char* __stdcall talasnica_getTradepacketInfo(void)
  {
		stringstream proud(ios_base::out);

		proud << tradePacket;
		//return (proud.str().c_str());
		string info = proud.str();
		//return(info.c_str());
		char *str;
		str = new char[info.length() + 1];
		strcpy(str, info.c_str());
		return str;
		
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

void __stdcall testSorting(void) {
	cout << "Talasnica testSorting()" << endl;

	//Talasnica::Order order0 = addOrder(4316628, "GBPUSD", 1259050941, 1, 0.10000000, 1.65350000, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	//Talasnica::Order order0((unsigned long)4316628, string("GBPUSD"), (unsigned int)1259050941, (unsigned short)1, 0.10000000, 1.65350000, 0.00000000, 0.00000000, (unsigned int)0, (unsigned int)0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, string(""), (unsigned int)0);
	//Talasnica::Order order((unsigned long)ticket, string(symbol), (unsigned int)openTime, (unsigned short)type, lots, openPrice, stopLoss, takeProfit, (unsigned int)expiration, (unsigned int)closeTime, closePrice, commission, profit, swap, string(comment), (unsigned int)magicNumber);
	Talasnica::Order order1(100, "GBPUSD", 1259050941, 1, 0.10000000, 1.6, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	Talasnica::Order order2(110, "GBPUSD", 1259137924, 0, 0.10000000, 1.7, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);
	Talasnica::Order order3(120, "GBPUSD", 1259050941, 1, 0.10000000, 1.5, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -5.97000000, -0.65000000, "", 0);
	Talasnica::Order order4(130, "GBPUSD", 1259137924, 0, 0.10000000, 1.9, 0.00000000, 0.00000000, 0, 0, 1.65440000, 0.00000000, -77.56000000, -0.22000000, "", 0);

	vector<Talasnica::Order> zasobnik;
	zasobnik.push_back(order1);
	zasobnik.push_back(order2);
	zasobnik.push_back(order3);
	zasobnik.push_back(order4);

	/*map<int,Talasnica::Order> zasobnik;
	zasobnik.insert(std::make_pair(order1.getTicket(),order1));
	zasobnik.insert(std::make_pair(order2.getTicket(),order2));
	zasobnik.insert(std::make_pair(order3.getTicket(),order3));
	zasobnik.insert(std::make_pair(order4.getTicket(),order4));*/
  
	for(unsigned int i = 0; i < zasobnik.size(); i++){
		cout << zasobnik[i] << endl;
	}

  /*
     Teï prvky vektoru seøadím sestupnì. Použiji stabilní øazení,
     i když zde se to nemá jak projevit!
  */
	/*vector<Talasnica::Order> vektor;
	vektor.reserve(zasobnik.size());*/
	//copy(zasobnik.begin(), zasobnik.end(), vektor.begin());
	//copy(zasobnik.begin(),zasobnik.end(),vektor);
	sort(zasobnik.begin(),zasobnik.end(),less<Talasnica::Order>());
  //copy(vektor.begin(),vektor.end(),ostream_iterator<Talasnica::Order>(cout,"\t"));
	cout << "serazeno podle ceny" << endl;
	for(unsigned int i = 0; i < zasobnik.size(); i++){
		cout << zasobnik[i] << endl;
	}
  cout << endl;
}