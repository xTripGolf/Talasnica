//+------------------------------------------------------------------+
//|                                           talasnica_multiOpen.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property show_inputs

#include <WinUser32.mqh>
#include <talasnica.inc-1.0.mqh>

#import "talasnica.lib-1.0.ex4"
   //bool tl_OrderSelect(int type, int index);
   //bool tl_OrderCnt();
   //int tl_OrderTicket();
   string tl_OrderName(int type);
   int tl_Log(string str, int errorLevel = 0);
   bool tl_OrderSend (int type, double volume, double price, double stoploss=0, double takeprofit=0, int magic = 0);
   double tl_OrderEnterPrice(int type = -1);
   int tl_OrderReverse(int type = -1);
#import

extern string text0 = "***** BUY LIMIT *****";
extern int daj_buy_limit_koliko = 0;
extern int daj_buy_limit_koliko_od_ask = 8;
extern int daj_buy_limit_okvir_mreze = 10;
extern double daj_buy_limit_lots = 0.1;
extern int daj_buy_limit_TP = 0;
extern int daj_buy_limit_SL = 0;

extern string text1 = "***** SELL LIMIT *****";
extern int daj_sell_limit_koliko = 0;
extern int daj_sell_limit_koliko_od_bid = 8;
extern int daj_sell_limit_okvir_mreze = 10;
extern double daj_sell_limit_lots = 0.1;
extern int daj_sell_limit_TP = 0;
extern int daj_sell_limit_SL = 0;

extern string text2 = "***** BUY STOP *****";
extern int daj_buy_stop_koliko = 1;
extern int daj_buy_stop_koliko_od_ask = 30;
extern int daj_buy_stop_okvir_mreze = 10;
extern double daj_buy_stop_lots = 1;
extern int daj_buy_stop_TP = 0;
extern int daj_buy_stop_SL = 0;

extern string text3 = "***** SELL STOP *****";
extern int daj_sell_stop_koliko = 1;
extern int daj_sell_stop_koliko_od_bid = 30;
extern int daj_sell_stop_okvir_mreze = 10;
extern double daj_sell_stop_lots = 1;
extern int daj_sell_stop_TP = 0;
extern int daj_sell_stop_SL = 0;

int toOpen[4];
//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
{
  
   tl_Log("STARTUJE TALASNICA MULTI OPEN SCRIPT", LOG_SCRIPT);
   
   //----
   
   //tl_OrderCnt();
   
   int type;
   int toOpen;
   
   for(int t=0; t<4; t++) {
     type = t+2;
     toOpen = toOpen(type);
     for(int i=0; i < toOpen; i++) {
       multiOpen(type, i);
     }

   }
   
   tl_Log("GOTOVO TALASNICA MULTI OPEN", LOG_SCRIPT);

   //----
   return(0);
}/*
//+------------------------------------------------------------------+
*/
bool multiOpen(int type, int i) {

   double _open, _tp, _sl; 
   
   _open = tl_OrderEnterPrice(type) + tl_OrderReverse(type) * distancja(type) * Point + i * tl_OrderReverse(type) * okvir(type) * Point;

   _tp = tp(type, _open);
   
   _sl = sl(type, _open);
   
   
   tl_OrderSend(type, lots(type), _open, _sl, _tp, 0);
}

int toOpen(int type) {

   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_koliko);
      case OP_SELLLIMIT:
         return(daj_sell_limit_koliko);
      case OP_BUYSTOP:
         return(daj_buy_stop_koliko);
      case OP_SELLSTOP:
         return(daj_sell_stop_koliko);
      default:
         return(0);
   }
}

int distancja(int type) {
   
   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_koliko_od_ask);
      case OP_SELLLIMIT:
         return(daj_sell_limit_koliko_od_bid);
      case OP_BUYSTOP:
         return(daj_buy_stop_koliko_od_ask);
      case OP_SELLSTOP:
         return(daj_sell_stop_koliko_od_bid);
      default:
         return(0);
   }
}

int okvir(int type) {
   
   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_okvir_mreze);
      case OP_SELLLIMIT:
         return(daj_sell_limit_okvir_mreze);
      case OP_BUYSTOP:
         return(daj_buy_stop_okvir_mreze);
      case OP_SELLSTOP:
         return(daj_sell_stop_okvir_mreze);
      default:
         return(0);
   }
}

double lots(int type) {
   
   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_lots);
      case OP_SELLLIMIT:
         return(daj_sell_limit_lots);
      case OP_BUYSTOP:
         return(daj_buy_stop_lots);
      case OP_SELLSTOP:
         return(daj_sell_stop_lots);
      default:
         return(0);
   }
}

int tp(int type, double open) {

   int tp = 0;

   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_TP);
      case OP_SELLLIMIT:
         return(daj_sell_limit_TP);
      case OP_BUYSTOP:
         return(daj_buy_stop_TP);
      case OP_SELLSTOP:
         return(daj_sell_stop_TP);
      default:
         return(0);
   }
   
   
   if(tp > 0) {
      tp = open + tl_OrderReverse(type) * tp * Point;
   }
   
   return(tp);
}

int sl(int type, double open) {
   
   int sl = 0;

   switch(type) {
      case OP_BUYLIMIT:
         return(daj_buy_limit_SL);
      case OP_SELLLIMIT:
         return(daj_sell_limit_SL);
      case OP_BUYSTOP:
         return(daj_buy_stop_SL);
      case OP_SELLSTOP:
         return(daj_sell_stop_SL);
      default:
         return(0);
   }
   
   if(sl > 0) {
      sl = open - tl_OrderReverse(type) * sl * Point;
   }
   
   return(sl);
}