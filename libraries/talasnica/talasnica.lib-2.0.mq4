//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#include "./../../include/talasnica.inc-2.0.mqh"

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import

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
   int colorIndex = 2 * OrderType(); // index v paletì _arrows_colors
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
   int colorIndex = 3 * OrderType(); // index v paletì ArrowColors
   bool closed = false;
   
 if (!GlobalVariableCheck("InTrade")) {
   while (tries < chance)
     {
      GlobalVariableSet("InTrade", TimeCurrent());  // set lock indicator
       
      if(OrderType() == OP_BUY) {
       closed = OrderClose(OrderTicket(), OrderLots(), Bid, Slippage, ArrowColors[colorIndex]);
      }
      else  if(OrderType() == OP_SELL) {
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
vybere obchod ze seynamu obchodù
param type - typ obchodu
param index - poøadí v poli
*/

bool tl_OrderSelect(int type, int index) {
   
   int ticket = talasnica_OrderSelect(type, index);
   
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
datetime tl_OrderType() {
   return(OrderType());
}
/****************************************************************
pomocné funkce pro obchodování
****************************************************************/

  int tl_OrderReverse(int type = -1) {

   if(type == -1) {
      type = OrderType();
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
      type = OrderType();
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

   int type = OrderType();
   
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

bool talasnica_recalculate(){
   
      //Print("Pøed resetem " + talasnica_getTradepacketInfo());
      talasnica_reset();
      //Print("Po resetu " + talasnica_getTradepacketInfo());
   
      for(int i = 0; i<OrdersTotal(); i++){
      if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES) && OrderSymbol()==Symbol() /*&& OrderComment() == tl_Comment()*/){
      /*Print(OrderTicket()+ ", " +
                             OrderSymbol()+ ", " +
                             OrderOpenTime()+ ", " +
                             OrderType()+ ", " +
                             OrderLots()+ ", " +
                             OrderOpenPrice()+ ", " +
                             OrderStopLoss()+ ", " +
                             OrderTakeProfit()+ ", " +
                             OrderExpiration()+ ", " +
                             OrderCloseTime()+ ", " +
                             OrderClosePrice()+ ", " +
                             OrderCommission()+ ", " +
                             OrderProfit()+ ", " +
                             OrderSwap()+ ", " +
                             OrderComment()+ ", " +
                             OrderMagicNumber()
                             );*/
         talasnica_addOrder(OrderTicket(),
                             OrderSymbol(),
                             OrderOpenTime(),
                             OrderType(),
                             OrderLots(),
                             OrderOpenPrice(),
                             OrderStopLoss(),
                             OrderTakeProfit(),
                             OrderExpiration(),
                             OrderCloseTime(),
                             OrderClosePrice(),
                             OrderCommission(),
                             OrderProfit(),
                             OrderSwap(),
                             OrderComment(),
                             OrderMagicNumber()
                             );
      }
   }
    return(true);
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