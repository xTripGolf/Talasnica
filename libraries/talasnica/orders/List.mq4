//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#include <talasnica.mqh>

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
//#import "talasnica/Log.ex4"
//   string tl_Log(string str, int errorLevel = 0);
#import

/**********************************
* poèítadlo obchodù  dle druhu
**********************************/
/*
* poèet obchodù
*/
int _C[DIMENZE_OP];
/**
* poèet lotù
*/
 double _V[DIMENZE_OP];
/**
* profit
*/
double _P[DIMENZE_OP];
/**
* swap
*/
double _Sw[DIMENZE_OP];
/**
* profit + swap
*/
double _PSw[DIMENZE_OP];
/**
* aproximovaná vstupní cena
*/
double _E[DIMENZE_OP];
/**
* suma vstupních cen pro výpoèet _E
*/
double _SumE[DIMENZE_OP];
/**
* pomocné úložištì obchodù
*/
int TradeList[]; // obsahuje tickety

/**
* seznam obchodù dle typu, seøazené dle ceny
*
* obsahuje cenu, tiket, loty, stopku a u otevøených ještì èistý profit (profit + swap)
* tickety obchodu, index prvního pole je level
*/
double Bulls[][7], Bears[][7], BullsLimit[][4], BearsLimit[][4], BullsStop[][4], BearsStop[][4];
#define A_PRICE 0
#define A_TICKET 1
#define A_VOLUME 2
#define A_SL 3
#define A_PROFIT 4
#define A_SWAP 5
#define A_PROFIT_SWAP 6

/****************************************************************
funkce pro poèítání obchodù
****************************************************************/

bool talasnica_OrderCnt(){

/******************
*
* první prùchod - naplní tradelist a spoèítá T, P, V, ...
*
*******************/
   talasnica_orders_izabraj();


/******************
*
* druhý prùchod prochází již jen obchody vlastního systému a páru (z tradeListu)
* naplní jejich seznam a seøadí podle otevírací ceny
*
*******************/
   
   //_poredjaj();
    

   
/******************
*
* tøetí prùchod vytváøí další skupiny
* 
*
*******************/  

   //_racunaj();

   // zámek
   
  
   return (true);
}

/******************
*
* první prùchod - naplní tradelist a spoèítá T, P, V, ...
*
*******************/

bool talasnica_orders_izabraj() {
   
   ArrayInitialize(_C,0); // poèet obchodù
   ArrayInitialize(_V,0); // poèet lotù
   ArrayInitialize(_P,0); // profit
   ArrayInitialize(_Sw,0); // swap
   ArrayInitialize(_E,0); // aproximovaná vstupní cena
   ArrayInitialize(_SumE,0); // suma vstupních cen
   ArrayInitialize(_PSw,0); // swap
   
   int index = 0;
   //double profit;
   int type;
   int key; // klic pro pole T, P, V pro profit, nebo loss
   
   ArrayResize(TradeList, OrdersTotal());
   
   for(int i = 0; i<OrdersTotal(); i++){
      if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES) && OrderSymbol()==Symbol() /*&& OrderComment() == tl_Comment()*/){
            
            TradeList[index] = OrderTicket();
            index++;
            type = OrderType();
            
            _C[type]++;
            _V[type] += OrderLots();          
            
            if(type < OP_BUYLIMIT) {
               _P[type] += OrderProfit();
               _Sw[type] += OrderSwap();
               _SumE[type] += OrderOpenPrice() * OrderLots();
            
               // spoèítáme profitové a ztrátové obchody bez rozdílu typu
               if((OrderProfit() + OrderSwap()) > 0) {
                 key = OP_PROFIT; 
               }
               else {
                  key = OP_LOSS;
               }
               _C[key]++;
               _V[key] += OrderLots();
               _P[key] += OrderProfit();
               
            }
      }
   }
   
    ArrayResize(TradeList, index);
    return(true);
}

/******************
*
* druhý prùchod prochází již jen obchody vlastního systému a páru (z tradeListu)
* naplní jejich seznam a seøadí podle otevírací ceny
*
*******************/

void talasnica_orders_poredjaj() {
   
   int i = 0;

   ArrayResize(Bulls, _C[OP_BUY]);
   ArrayResize(Bears, _C[OP_SELL]);
   ArrayResize(BullsLimit, _C[OP_BUYLIMIT]);
   ArrayResize(BearsLimit, _C[OP_SELLLIMIT]);
   ArrayResize(BullsStop, _C[OP_BUYSTOP]);
   ArrayResize(BearsStop, _C[OP_SELLSTOP]);
   
   if(_C[OP_BUY] > 0) {
      ArrayInitialize(Bulls,0);
   }
   if(_C[OP_SELL] > 0) {
      ArrayInitialize(Bears,0);
   }
   if(_C[OP_BUYLIMIT] > 0) {
      ArrayInitialize(BullsLimit,0);
   }
   if(_C[OP_SELLLIMIT] > 0) {
      ArrayInitialize(BearsLimit,0);
   }
   if(_C[OP_BUYSTOP] > 0) {
      ArrayInitialize(BullsStop,0);
   }
   if(_C[OP_SELLSTOP] > 0) {
      ArrayInitialize(BearsStop,0);
   }
   
   int counter[6];
   ArrayInitialize(counter,0);

   for(i = 0; i < ArraySize(TradeList); i++) {
      OrderSelect(TradeList[i], SELECT_BY_TICKET);
      switch(OrderType()) {
         case OP_BUY:
            Bulls[counter[OP_BUY]][A_PRICE] = OrderOpenPrice();
            Bulls[counter[OP_BUY]][A_VOLUME] = OrderLots();
            Bulls[counter[OP_BUY]][A_TICKET] = OrderTicket();
            Bulls[counter[OP_BUY]][A_SL] = OrderStopLoss();
            Bulls[counter[OP_BUY]][A_PROFIT] = OrderProfit();
            Bulls[counter[OP_BUY]][A_PROFIT_SWAP] = OrderProfit() + OrderSwap();
            Bulls[counter[OP_BUY]][A_SWAP] = OrderSwap();
            
            counter[OP_BUY]++;
            
            break;
         case OP_SELL:       
            Bears[counter[OP_SELL]][A_PRICE] = OrderOpenPrice();
            Bears[counter[OP_SELL]][A_VOLUME] = OrderLots();
            Bears[counter[OP_SELL]][A_TICKET] = OrderTicket();
            Bears[counter[OP_SELL]][A_SL] = OrderStopLoss();
            Bears[counter[OP_SELL]][A_PROFIT] = OrderProfit();
            Bears[counter[OP_SELL]][A_PROFIT_SWAP] = OrderProfit() + OrderSwap();
            Bears[counter[OP_SELL]][A_SWAP] = OrderSwap();
                                 
            counter[OP_SELL]++;
            
            break;
         case OP_BUYSTOP:
            BullsStop[counter[OP_BUYSTOP]][A_PRICE] = OrderOpenPrice();
            BullsStop[counter[OP_BUYSTOP]][A_VOLUME] = OrderLots();
            BullsStop[counter[OP_BUYSTOP]][A_TICKET] = OrderTicket();
            BullsStop[counter[OP_BUYSTOP]][A_SL] = OrderStopLoss();
            
            counter[OP_BUYSTOP]++;
            
            break;
         case OP_SELLSTOP:
            BearsStop[counter[OP_SELLSTOP]][A_PRICE] = OrderOpenPrice();
            BearsStop[counter[OP_SELLSTOP]][A_VOLUME] = OrderLots();
            BearsStop[counter[OP_SELLSTOP]][A_TICKET] = OrderTicket();
            BearsStop[counter[OP_SELLSTOP]][A_SL] = OrderStopLoss();
            
            counter[OP_SELLSTOP]++;
            
            break;                              
      }
   }

   // seøadíme pole bulls 
   if(_C[OP_BUY] > 0) { 
      ArraySort(Bulls, WHOLE_ARRAY, 0, MODE_ASCEND);
   }
   
   // seøadíme pole bears
   if(_C[OP_SELL] > 0) {
      ArraySort(Bears, WHOLE_ARRAY, 0, MODE_DESCEND);
   }

   // seøadíme pole BullsStop 
   if(counter[OP_BUYSTOP] > 0) {
      ArraySort(BullsStop, WHOLE_ARRAY, 0, MODE_ASCEND);
   }

   // seøadíme pole BearsStop    
   if(counter[OP_SELLSTOP] > 0) {
      ArraySort(BearsStop, WHOLE_ARRAY, 0, MODE_DESCEND);
   }
   
   return(true);
}

/********************
* funkce pro výpoèet výstupních hodnot
********************/
/*
bool _racunaj() {
     
    int i = 0;
     
    _C[OP_OPENED] = _C[OP_BUY] - _C[OP_SELL];
     
    _V[OP_OPENED] = _V[OP_BUY] - _V[OP_SELL];
    
    _P[OP_OPENED] = _P[OP_BUY] + _P[OP_SELL];
    
    _SumE[OP_OPENED] = _SumE[OP_BUY] - _SumE[OP_SELL];
    
    _Sw[OP_OPENED] = _Sw[OP_BUY] + _Sw[OP_SELL];
    
   
   // pøevislé obchody
   
   int previs = tl_Previs();
   
   _SumE[OP_PREMOC] = 0;
   _V[OP_PREMOC] = 0;
   
   if(previs > 0) {
      _C[OP_PREMOC] = previs;
      for(i = 0; i < previs; i++) {
         _SumE[OP_PREMOC] += Bulls[i][A_PRICE] * Bulls[i][A_VOLUME];
         _V[OP_PREMOC] += Bulls[i][A_VOLUME];
         _P[OP_PREMOC] += Bulls[i][A_PROFIT];
         _Sw[OP_PREMOC] += Bulls[i][A_SWAP];
      }
   }
   
   if(previs < 0) {
      _C[OP_PREMOC] = previs;
      previs = -1 * previs;
      for(i = 0; i < previs; i++) {
         _SumE[OP_PREMOC] -= Bears[i][A_PRICE] * Bears[i][A_VOLUME];
         _V[OP_PREMOC] -= Bears[i][A_VOLUME];
         _P[OP_PREMOC] += Bears[i][A_PROFIT];
         _Sw[OP_PREMOC] += Bears[i][A_SWAP];
      }
   }
   
  // dopocet
  
     for(i = 0; i < ArraySize(_E); i++) {
      if(_V[i] != 0) {
         _E[i] = _SumE[i] / _V[i];
      }
    }
    
   for(i = 0; i < ArraySize(_PSw); i++) {
      _PSw[i] = _P[i] + _Sw[i];
    }
    
    /***********************************/
    
   // výstup s odloženými obchody
  /* 
   double _v, _c, _sumE, _e, volume, price;
   bool derivace = false;
   double rozestup = 0.0014;
   
   _V[OP_SVETAURUS] = 0;
   _SumE[OP_SVETAURUS] = _SumE[OP_OPENED];
   _E[OP_SVETAURUS] = 0;
   
   _sumE = _SumE[OP_OPENED];
   _v = _V[OP_OPENED];
   _c = _C[OP_OPENED];
   _e = 0;
   i = 0;
   price = Ask;
   volume = Lots;

   derivace = false;

   
   while (derivace == false) {
      i++;
      if(i < _C[OP_BUYSTOP]) {
         volume = tl_getValue(OP_BUYSTOP, i, A_VOLUME);
         price = tl_getValue(OP_BUYSTOP, i, A_PRICE);
      }
      else {
         volume = Lots;
         price +=  rozestup;
      }
      _sumE += volume * price;
      _v += volume;
      _c++;
      
      if(_v <= 0) { // ještì není pøevis
         continue;
      }
      
      _e = _sumE / _v;

      if (_E[OP_SVETAURUS] == 0 || _E[OP_SVETAURUS] > _e) {
         _E[OP_SVETAURUS] = _e;
         _V[OP_SVETAURUS] = _v;
         _C[OP_SVETAURUS] = _c;
      }
      else {
         derivace = true;
      }
      
      
   }

   // totéž sell
   
   _V[OP_SVEMEDVED] = 0;
   _SumE[OP_SVEMEDVED] = _SumE[OP_OPENED];
   _E[OP_SVEMEDVED] = 0;
   
   _sumE = _SumE[OP_OPENED];
   _v = _V[OP_OPENED];
   _c = _C[OP_OPENED];
   _e = 0;
   i = 0;
   price = Bid;
   volume = Lots;
   
   derivace = false;

   while (derivace == false) {
      i++;
      if(i < _C[OP_SELLSTOP]) {
         volume = tl_getValue(OP_SELLSTOP, i, A_VOLUME);
         price = tl_getValue(OP_SELLSTOP, i, A_PRICE);
         //Print("medved STOP price " + price);
      }
      else {
         volume = Lots;
         price -= rozestup;
         //Print("medved FIKTIVE price " + price);
      }
      
      if(price < 0) {
         Print("Mensi nule, konec");
         derivace = true;
      }
      _sumE -= volume * price;
      _v -= volume;
      _c--;
      
      if(_v >= 0) { // ještì není pøevis
         continue;
      }
      
      _e = _sumE / _v;
      
      if (_E[OP_SVEMEDVED] == 0 || _E[OP_SVEMEDVED] < _e) {
         //Print("medved _e " + _e);
         _E[OP_SVEMEDVED] = _e;
         _V[OP_SVEMEDVED] = _v;
         _C[OP_SVEMEDVED] = _c;
      }
      else {
         derivace = true;
      }
      
      
   }
} //end _racunaj
*/