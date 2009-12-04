//+------------------------------------------------------------------+
//|                                           talasnica_panClose.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property show_inputs

#include <WinUser32.mqh>
#include <talasnica.inc-1.0.mqh>

#import "talasnica.lib-1.0.ex4"
   bool tl_OrderSelect(int type, int index);
   bool tl_OrderCnt();
   int tl_OrderTicket();
   string tl_OrderName(int type);
   int tl_Log(string str, int errorLevel = 0);
   int tl_OrderReverse(int type = -1);
   double tl_OrderTakeProfit();
   double tl_OrderOpenPrice();
   double tl_OrderStopLoss();
   bool tl_OrderModify (double price, double stoploss = 0, double takeprofit = 0);
#import

extern int mrdaj_buy_limit = 0;
extern int mrdaj_sell_limit = 0;
extern int mrdaj_buy_stop = 0;
extern int mrdaj_sell_stop = 0;

//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
  
   tl_Log("STARTUJE TALASNICA PAN MOVE SCRIPT", LOG_SCRIPT);
   
   //----
   
   tl_OrderCnt();
   
   int mrdaj[4];
   mrdaj[0] = mrdaj_buy_limit;
   mrdaj[1] = mrdaj_sell_limit;
   mrdaj[2] = mrdaj_buy_stop;
   mrdaj[3] = mrdaj_sell_stop;
   
   int type;
   
   for(int i = 0; i<4; i++) {
     type = i + 2;
     if(mrdaj[i] != 0) {
       panMove(type, mrdaj[i]);
     }
   }

   tl_Log("GOTOVO TALASNICA PAN MOVE", LOG_SCRIPT);

   //----
   return(0);
  }
//+------------------------------------------------------------------+

bool panMove(int type, int pipsMove) {
   int i = 0;
   double posun = pipsMove * Point;
   double op, tp, sl;
   double fromPrice;
   int reverse;
   
   int potvrda = MessageBox("Da li èemo da pomerimo sve " + tl_OrderName(type), "pomeraj " + tl_OrderName(type), MB_OKCANCEL);
   
   if(potvrda == IDCANCEL) {
      tl_Log("CANCEL " + tl_OrderName(type), LOG_SCRIPT);
      return(False);
   }
   
      tl_Log("MOVE ALL " + tl_OrderName(type), LOG_SCRIPT);
   
   while(tl_OrderSelect(type, i)) {
      i++;
      reverse = tl_OrderReverse(type);
      fromPrice = tl_OrderOpenPrice();
      op = fromPrice + reverse * posun;
      sl = tl_OrderStopLoss();
      tp = tl_OrderTakeProfit();
      if(sl > 0) {
         sl += reverse * posun;
      }
      if(tp > 0) {
         tp += reverse * posun;
      }
      if(tl_OrderModify (op, sl, tp)) {
         tl_Log(tl_OrderTicket() + " moved from " + fromPrice + " to " + op, LOG_SCRIPT);
      }
      else {
         tl_Log(tl_OrderTicket() + " error", LOG_ERROR);
      }
      
   }
}