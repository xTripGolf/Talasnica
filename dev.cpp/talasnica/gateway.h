#pragma once
#define TALASNICA  // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <iostream>

#include "talasnica.h"
#include "Exception.h"
#include "OrdersManager.h"
#include "Order.h"

//----
#define MT4_EXPFUNC __declspec(dllexport)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

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
MT4_EXPFUNC void __stdcall talasnica_sortOrders(void);
MT4_EXPFUNC void __stdcall talasnica_reset(void);
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù dle druhu
   */
MT4_EXPFUNC int __stdcall talasnica_packetCount(int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * poèet lotù
   */
MT4_EXPFUNC double __stdcall talasnica_packetVolume(int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * profit
   */
MT4_EXPFUNC double __stdcall talasnica_packetProfit(int packetFilter);
   /**
   * swap
   *
   */
MT4_EXPFUNC double __stdcall talasnica_packetSwap(int packetFilter);
   /**
   * profit + swap
   *
   */
MT4_EXPFUNC double __stdcall talasnica_packetTotalProfit(int packetFilter);
   /**
   * aproximovaná vstupní cena
   *
   */
MT4_EXPFUNC double __stdcall talasnica_packetOpenPrice(int packetFilter);
   /**
   * vybere obchod
   *
   */
MT4_EXPFUNC int __stdcall talasnica_getTicket(int packetFilter, int index);
   /**
   * vrátí název paketu obchodù
   *
   */
MT4_EXPFUNC char* __stdcall talasnica_packetName(int packetFilter);
   /**
   * vrátí popis paketu obchodù
   *
   */
MT4_EXPFUNC char* __stdcall talasnica_packetDescription(int packetFilter);

