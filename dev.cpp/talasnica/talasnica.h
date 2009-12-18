#pragma once
#define TALASNICA  // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include<vector>
//#include <cstring>
#include "TradePacket.h"
#include "Order.h"

//----
#define MT4_EXPFUNC __declspec(dllexport)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct RateInfo
  {
   unsigned int      ctm;
   double            open;
   double            low;
   double            high;
   double            close;
   double            vol;
  };
#pragma pack(pop)
//----
struct MqlStr
  {
   int               len;
   char             *string;
  };
MT4_EXPFUNC int __stdcall talasnica_addOrder(const int ticket,
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
											const int magicNumber
	);
MT4_EXPFUNC void __stdcall talasnica_reset(void);
MT4_EXPFUNC char* __stdcall talasnica_getTradepacketInfo(void);
// sample
MT4_EXPFUNC int __stdcall GetIntValue(const int ipar);
MT4_EXPFUNC double __stdcall GetDoubleValue(const double dpar);
MT4_EXPFUNC char* __stdcall GetStringValue(char *spar);
MT4_EXPFUNC double __stdcall GetArrayItemValue(const double *arr,const int arraysize,const int nitem);
MT4_EXPFUNC BOOL __stdcall SetArrayItemValue(double *arr,const int arraysize,const int nitem,const double value);
MT4_EXPFUNC double __stdcall GetRatesItemValue(const RateInfo* rates,const int rates_total,const int shift,const int nrate);
MT4_EXPFUNC int __stdcall SortStringArray(MqlStr *arr,const int arraysize);
MT4_EXPFUNC int __stdcall ProcessStringArray(MqlStr *arr,const int arraysize);


MT4_EXPFUNC void __stdcall testSorting(void);