//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#include "./../include/talasnica.inc-1.0.mqh"

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import

/**
* poèítadlo obchodù
*
* poèet obchodù dle druhu
*/
int _C[DIMENZE_OP];
/**
* poèítadlo obchodù
*
* poèet lotù
*/
 double _V[DIMENZE_OP];
/**
* poèítadlo obchodù
*
* profit
*/
double _P[DIMENZE_OP];
/**
* swap
*
*/
double _Sw[DIMENZE_OP];
/**
* profit + swap
*
*/
double _PSw[DIMENZE_OP];
/**
* aproximovaná vstupní cena
*
*/
double _E[DIMENZE_OP];

double _SumE[DIMENZE_OP];

int TradeList[];

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

/**
* barvy pro 6 typu obchodu
*
* vždy pro 6 typù obchodù OP_BUY, ... OP_SELLSTOP, tj. 0 - 6
* pro každý typ 3 akce
* prvnich 6 prvkù pole je pro open každého typu obchodu
* dalsich 6 pro modify
* poslednich 6 pro delete/close
*/
color ArrowColors[18] = {Tomato, RoyalBlue, DeepPink, DarkTurquoise, Red, Blue, Yellow, Violet, Gold, Orchid, Gold, Orchid, Cornsilk, WhiteSmoke, Cornsilk, WhiteSmoke, Cornsilk, WhiteSmoke};

extern int Slippage=3;
double Lots = 0.1;
//+------------------------------------------------------------------+
//| My function                                                      |
//+------------------------------------------------------------------+
// int MyCalculator(int value,int value2)
//   {
//    return(value+value2);
//   }
//+------------------------------------------------------------------+

/**
*
*
*/

bool tl_setLots(double lots) {
   Lots = lots;
   return(true);
}


/**
* id obchodního systému
*
*/

string tl_Id() {
   return("talasnica");
}

/**
* komentáø pro oznaèení obchodù
*
*/

string tl_Comment() {
   return (tl_Id() + " " + Symbol());
   
}
/**
* vrací cestu k log souboru
*
*/

string tl_JournalFileName () {
   return (AccountName() + "/" + tl_Id() + "_" + Symbol() + "_ "+ Year() + "-" + Month() + "-" + Day() + ".log");
}

/**
* aktuální èas jako øetìzec
*/

string tl_Vcil() {
   return (Symbol() + " at " + TimeToStr(TimeCurrent(),TIME_DATE|TIME_SECONDS));
}

/*****************************************
trading
******************************************/

/*** NEW ORDER  ***/

int tl_OrderSend (int type, double volume, double price, double stoploss=0, double takeprofit=0, int magic = 0) {

   int ticket = -1; // návratová hodnota, èíslo ticketu
   int chance = 3; // poèet pokusù
   int tries = 0; // poèítadlo pokusù
 
 if (!GlobalVariableCheck("InTrade")) {
   while (tries < chance)
     {
       GlobalVariableSet("InTrade", TimeCurrent());  // set lock indicator
       ticket = OrderSend(Symbol(),type,volume,price,Slippage,stoploss,takeprofit,tl_Comment(),magic,0,ArrowColors[type]);
       //tl_Log("in function _OrderSend() Executed , ticket ="+ticket, LOG_);
       GlobalVariableDel("InTrade");   // clear lock indicator
       if(ticket<=0) {
         tl_Log("ERROR on _OrderSend () : "+ErrorDescription(GetLastError())+" of enterPrice @ "+price+" SL @ "+stoploss+" TP @ "+takeprofit+" lots @"+volume);
         tries++;
       } else tries = chance;
    }
  }
  else {
      tl_Log("ERROR on _OrderSend() : GlobalVariableCheck exists - " + ErrorDescription(GetLastError()) + " - ticket = " + ticket + " of enterPrice = "+price+" SL = "+stoploss+" TP = "+takeprofit);
  }
  return(ticket);
} // end tl_OrderSend()

/*** MODIFY ORDER  ***/

bool tl_OrderModify (double price, double stoploss = 0, double takeprofit = 0) {
   int chance = 3; // poèet pokusù
   int tries = 0; // poèítadlo pokusù
   int colorIndex = 2 * Talasnica::Type::Order(); // index v paletì _arrows_colors
   bool modified = false;
 
   price = NormalizeDouble(price, Digits);
   stoploss = NormalizeDouble(stoploss, Digits);
   takeprofit = NormalizeDouble(takeprofit, Digits);
 
   if(NormalizeDouble(OrderOpenPrice(), Digits) == price && NormalizeDouble(OrderStopLoss(), Digits) == stoploss && NormalizeDouble(OrderTakeProfit(), Digits) == takeprofit) {
      //Print("_OrderModify() - not modified ticket " + OrderTicket() + " not change");
      return (false);
   }
   
 if (!GlobalVariableCheck("InTrade")) {
   while (tries < chance)
     {
       GlobalVariableSet("InTrade", TimeCurrent());  // set lock indicator
       
      modified = OrderModify(OrderTicket(),price,stoploss,takeprofit,0,ArrowColors[colorIndex]);
       GlobalVariableDel("InTrade");   // clear lock indicator
       if(modified == false) {
         tries++;
       } else tries = chance;
    }
    
    if(modified == false) {
      tl_Log("ERROR on _OrderModify () : "+ErrorDescription(GetLastError()) + " - ticket = " + OrderTicket(), LOG_);
      tl_Log("price: " + OrderOpenPrice() + " -> " + price, LOG_);
      tl_Log("SL: " + OrderStopLoss() + " -> " + stoploss, LOG_);
      tl_Log("TP: " + OrderTakeProfit() + " -> " + takeprofit, LOG_);
      tl_Log("***", LOG_);
    }
  }
  else {
  
   if(modified == false) {
      tl_Log("ERROR on _OrderModify () : GlobalVariableCheck exists - "+ErrorDescription(GetLastError()) + " - ticket = " + OrderTicket() + " of enterPrice = "+price+" SL = "+stoploss+" TP = "+takeprofit, LOG_);
   }
  }
  
  return(modified); 
} // end tl_OrderModify

/*** CLOSE OR DELETE ORDER ***/

bool tl_OrderClose () {
   int chance = 3; // poèet pokusù
   int tries = 0; // poèítadlo pokusù
   int colorIndex = 3 * Talasnica::Type::Order(); // index v paletì ArrowColors
   bool closed = false;
   
 if (!GlobalVariableCheck("InTrade")) {
   while (tries < chance)
     {
      GlobalVariableSet("InTrade", TimeCurrent());  // set lock indicator
       
      if(Talasnica::Type::Order() == OP_BUY) {
       closed = OrderClose(OrderTicket(), OrderLots(), Bid, Slippage, ArrowColors[colorIndex]);
      }
      else  if(Talasnica::Type::Order() == OP_SELL) {
       closed = OrderClose(OrderTicket(), OrderLots(), Ask, Slippage, ArrowColors[colorIndex]);
      }
      else {
       closed = OrderDelete(OrderTicket(), ArrowColors[colorIndex]);
      }  
      GlobalVariableDel("InTrade");   // clear lock indicator
      if(closed == false) {
         tl_Log("ERROR on _OrderClose () : "+ErrorDescription(GetLastError())+" ticket = " + OrderTicket(), LOG_);
         tries++;
      } else tries = chance;
    }
  }
  else {
  
   if(closed == false) {
      tl_Log("ERROR on _OrderClose () : GlobalVariableCheck exists - "+ErrorDescription(GetLastError()) + " - ticket = " + OrderTicket(), LOG_);
   }
  }
  return(closed); 
} // end _OrderClose

/*** ORDER SELECT ***/
/*
vybere obchod z bulls/bears polí
param type - typ obchodu
param index - poøadí v poli
*/

bool tl_OrderSelect(int type, int index) {
   
   if(index >= _C[type]) {
      //Print ("Error in _OrderSelect() index out of range index = " + index + " type = " + type);
      return (false);
   }

   int ticket;
   
   switch (type) {
      case OP_BUY:
        ticket = Bulls[index][A_TICKET];
        break;
      case OP_SELL:
        ticket = Bears[index][A_TICKET];
        break;
      case OP_BUYLIMIT:
         ticket = BullsLimit[index][A_TICKET];
         break;
      case OP_SELLLIMIT:
         ticket = BearsLimit[index][A_TICKET];
         break;
      case OP_BUYSTOP:
        ticket = BullsStop[index][A_TICKET];
        break;
      case OP_SELLSTOP:
        ticket = BearsStop[index][A_TICKET];
        break;
      default:
         tl_Log ("Error in _OrderSelect() undefined type = " + type, LOG_);
         return (false);
   }
   
   bool ret = OrderSelect(ticket, SELECT_BY_TICKET);
   
   if(!ret) {
      tl_Log ("Error in _OrderSelect() ticket = " + ticket + " : " + ErrorDescription(GetLastError()), LOG_);
   }
   
   return (ret);
   
}

double tl_OrderTakeProfit() {
   return(NormalizeDouble(OrderTakeProfit(), Digits));
}

double tl_OrderOpenPrice() {
   return(NormalizeDouble(OrderOpenPrice(), Digits));
}

double tl_OrderStopLoss() {
   return(NormalizeDouble(OrderStopLoss(), Digits));
}

int tl_OrderTicket() {
   return(OrderTicket());
}

double tl_OrderLots() {
   return(OrderLots());
}


string tl_OrderSymbol() {
   return(OrderSymbol());
}

double tl_OrderClosePrice() {
   return(OrderClosePrice());
}
double tl_OrderSwap() {
   return(OrderSwap());
}
double tl_OrderProfit() {
   return(OrderProfit());
}
double tl_OrderProfitSwap() {
   return(OrderProfit() + OrderSwap());
}
string tl_OrderComment() {
   return(OrderComment());
}
datetime tl_OrderOpenTime() {
   return(OrderOpenTime());
}
datetime tl_Talasnica::Type::Order() {
   return(Talasnica::Type::Order());
}
/****************************************************************
pomocné funkce pro obchodování
****************************************************************/

  int tl_OrderReverse(int type = -1) {

   if(type == -1) {
      type = Talasnica::Type::Order();
   }
   
     switch (type) {
         case OP_BUY:
         case OP_BUYLIMIT:
         case OP_BUYSTOP:
            return(1);
         case OP_SELL:
         case OP_SELLLIMIT:
         case OP_SELLSTOP:
            return(-1);
         default:
            return (0); 
      }
} // end tl_OrderReverse()

  double tl_OrderEnterPrice(int type = -1) {

   if(type == -1) {
      type = Talasnica::Type::Order();
   }
   
     switch (type) {
         case OP_BUY:
         case OP_BUYLIMIT:
         case OP_BUYSTOP:
            return(Ask);
         case OP_SELL:
         case OP_SELLLIMIT:
         case OP_SELLSTOP:
            return(Bid);
         default:
            return (-1); 
      }
} // end tl_OrderEnterPrice()

  double tl_OrderOutputPrice() {

   int type = Talasnica::Type::Order();
   
     switch (type) {
         case OP_BUY:
         case OP_BUYLIMIT:
         case OP_BUYSTOP:
            return(Bid);
         case OP_SELL:
         case OP_SELLLIMIT:
         case OP_SELLSTOP:
            return(Ask);
         default:
            return (-1); 
    }
} // end tl_OrderOutputPrice()

string tl_OrderName(int type) {
   switch (type) {
     case OP_BUY:
         return("buy");
     case OP_SELL:
         return("sell");
     case OP_BUYLIMIT:
         return("limit buy");
     case OP_SELLLIMIT:
         return("limit sell");
     case OP_BUYSTOP:
         return("stop buy");
     case OP_SELLSTOP:
         return("stop sell");
     case OP_PROFIT:
         return("profit");
     case OP_LOSS:
         return("loss");
     case OP_OPENED:
         return("opened");
     case OP_PREMOC:
         return("premoc");    
     case OP_SVETAURUS:
         return("svetaurus");
     case OP_SVEMEDVED:
         return("svemedved");
     default:
         return("unknown");
   }
 }
/****************************************************************
funkce pro poèítání obchodù
****************************************************************/

bool tl_OrderCnt(){

/******************
*
* první prùchod - naplní tradelist a spoèítá T, P, V, ...
*
*******************/
   _izabraj();


/******************
*
* druhý prùchod prochází již jen obchody vlastního systému a páru (z ordersPoolu)
* naplní jejich seznam a seøadí podle otevírací ceny
*
*******************/
   
   _poredjaj();
    

   
/******************
*
* tøetí prùchod vytváøí další skupiny
* 
*
*******************/  

   _racunaj();

   // zámek
   
  
   return (true);
}

/******************
*
* první prùchod - naplní tradelist a spoèítá T, P, V, ...
*
*******************/

bool _izabraj() {
   
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
            type = Talasnica::Type::Order();
            
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
* druhý prùchod prochází již jen obchody vlastního systému a páru (z ordersPoolu)
* naplní jejich seznam a seøadí podle otevírací ceny
*
*******************/

void _poredjaj() {
   
   int i = 0;

   ArrayResize(Bulls, _C[OP_BUY]);
   ArrayResize(Bears, _C[OP_SELL]);
   // limity nepoužívám
   // možno doplnit kad bude treba
   ArrayResize(BullsStop, _C[OP_BUYSTOP]);
   ArrayResize(BearsStop, _C[OP_SELLSTOP]);
   
   if(_C[OP_BUY] > 0) {
      ArrayInitialize(Bulls,0);
   }
   if(_C[OP_SELL] > 0) {
      ArrayInitialize(Bears,0);
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
      switch(Talasnica::Type::Order()) {
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
} //end tl_calcOutput

int tl_Previs() {
   return (_C[OP_BUY] - _C[OP_SELL]);
}

int tl_Zamceno() {
   return(MathMin(_C[OP_BUY], _C[OP_SELL]));
}

int tl_Otevreno() {
   return (MathMax(_C[OP_BUY], _C[OP_SELL]));
}

bool tl_selectMaxLos () {
   
   double bProfit = 0;
   double sProfit = 0;
   bool sel;
   
   sel = tl_OrderSelect(OP_BUY, _C[OP_BUY] - 1);
   if(sel) {
      bProfit = tl_OrderProfit() + tl_OrderSwap();
      }
    
   sel = tl_OrderSelect(OP_SELL, _C[OP_SELL] - 1);
   if(sel) {
      sProfit = tl_OrderProfit() + tl_OrderSwap();
      if(sProfit > bProfit) {
         sel = tl_OrderSelect(OP_BUY, _C[OP_BUY] - 1);
      }
   }
   
   return(sel);
}
  
/**
***/

int tl_C(int type) {
   return(_C[type]);
}

double tl_V(int type) {
   return(_V[type]);
}

double tl_P(int type) {
   return(_P[type]);
}

double tl_Sw(int type) {
   return(_Sw[type]);
}

double tl_E(int type) {
   return(_E[type]);
}

double tl_PSw(int type) {
   return(_PSw[type]);
}

/**
* kontroluje, zda cena pro odložený obchod není pøíliš blízko již otevøenému obchodu
*
*
*/

double tl_MedziTaure (double enter, int mezera) {
   //Print("MEDZITAURE enter + " + enter + " na medzeru " + mezera);
   if (mezera == 0) {
      return (enter);
   }

   double diff;
   for(int i = 0; i < tl_C(OP_BUY); i++) { 
     diff = MathAbs(enter - Bulls[i][A_PRICE]);
     //Print(i + " medzi taure enter " + enter + " - " + Bulls[i][A_PRICE] + " diff " + diff); 
     if(diff < mezera * Point) {
         //Print("ITERACE v kroku " + i);
         enter = tl_MedziTaure(enter + (mezera + 1) * Point - diff, mezera);
         return (enter);
     }
   }
   //Print("RETURN " + enter);
   return(NormalizeDouble(enter, Digits));

}


double tl_MedziMedvede (double enter, int mezera) {
   //Print("MEDZIMEDVEDE enter + " + enter + " na medzeru " + mezera);
   if (mezera == 0) {
      return(enter);
   }

   double diff;
      for(int i = 0; i < tl_C(OP_SELL); i++) {   
        diff = MathAbs(enter - Bears[i][A_PRICE]);
        //Print(i + " medzi medvede enter " + enter + " - " + Bears[i][A_PRICE] + " diff " + diff); 
        if(diff < mezera * Point) {
         //Print("ITERACE v kroku " + i);
         enter = tl_MedziMedvede (enter - (mezera + 1) * Point + diff, mezera);
         return (enter);
       }
      }
   //Print("RETURN " + enter);
   return(NormalizeDouble(enter, Digits));

}

/**
*
* int type typ obchodu
* int index poøadí obchodu
* int parameter typ informace
*/
double tl_getValue(int type, int index, int parameter) {

   switch (type) {
      case OP_BUY:
         return(Bulls[index][parameter]);
      case OP_SELL:
         return(Bears[index][parameter]);
      case OP_BUYSTOP:
         return(BullsStop[index][parameter]);
      case OP_SELLSTOP:
         return(BearsStop[index][parameter]);
      case OP_BUYLIMIT:
         return(BullsLimit[index][parameter]);
      case OP_SELLLIMIT:
         return(BearsLimit[index][parameter]);
      default:
         break;
   }  
}

double tl_getProfit (int type, int index) {

   return(tl_getValue(type, index, A_PROFIT_SWAP));
}

double tl_getTicket (int type, int index) {

   return(tl_getValue(type, index, A_TICKET));
}

/*****************************************
konverzní funkce
******************************************/
/*
   double tl_Pips2Points(int par) {
      double ret = par;
      return ret * Point;
   }*/

   double tl_Pips2Money(int par) {
      double ret = par;
      double pipsValue = MarketInfo(Symbol(), MODE_TICKVALUE);
      return (ret * pipsValue);
   }
   
   double tl_Money2Pips(int par) {
      double ret = par;
      double pipsValue = MarketInfo(Symbol(), MODE_TICKVALUE);
      return (ret / pipsValue);
   }


/*****************************************
loging
******************************************/

/**
* zapíše øetìzec do logovacího souboru
*/
 
 int tl_Log(string str, int errorLevel = 0)
{
   int handle;
 
   handle = FileOpen(tl_JournalFileName(), FILE_CSV|FILE_WRITE|FILE_READ, ';');
   if(handle < 1)
   {
     Print("can't open journal file. Error-" + ErrorDescription(GetLastError()));
   }
   else {
      FileSeek(handle,0,SEEK_END);
      str = tl_Vcil() + "\t" + str;
      FileWrite(handle, str);
   } 
   FileClose(handle);
   //Print("LOG level " + errorLevel);
   //Print(">> " + str);
}