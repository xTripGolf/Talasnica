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
//#import "talasnica/InfoBox.ex4"
   //void LabelCreate(string _LabelName, int _OsaX, int _OsaY, int _Roh = 2, string _Text = "", int _FontSize = 12, color _Color = Yellow);
   //string formatText2Cell(string text, int cellSize = 12);
#import

#define UNKNOWN_NAME "UNKNOWN NAME"
#define UNKNOWN_DESCRIPTION "UNKNOWN DESCRIPTION"

/**********************************************************************

***********************************************************************/

//extern int InfoboxFontSize = 10;
//extern string InfoboxFontName = "Courier";
/*
extern bool show_MODE_LOW = true;// 1 Low day price. 
extern bool show_MODE_HIGH = true;// 2 High day price. 
extern bool show_MODE_TIME = true;// 5 The last incoming tick time (last known server time). 
extern bool show_MODE_BID = true;// 9 Last incoming bid price. For the current symbol, it is stored in the predefined variable Bid 
extern bool show_MODE_ASK = true;// 10 Last incoming ask price. For the current symbol, it is stored in the predefined variable Ask 
extern bool show_MODE_POINT = true;// 11 Point size in the quote currency. For the current symbol, it is stored in the predefined variable Point 
extern bool show_MODE_DIGITS = true;// 12 Count of digits after decimal point in the symbol prices. For the current symbol, it is stored in the predefined variable Digits 
extern bool show_MODE_SPREAD = true;// 13 Spread value in points. 
extern bool show_MODE_STOPLEVEL = true;// 14 Stop level in points. 
extern bool show_MODE_LOTSIZE = true;// 15 Lot size in the base currency. 
extern bool show_MODE_TICKVALUE = true;// 16 Tick value in the deposit currency. 
extern bool show_MODE_TICKSIZE = true;// 17 Tick size in the quote currency. 
extern bool show_MODE_SWAPLONG = true;// 18 Swap of the long position. 
extern bool show_MODE_SWAPSHORT = true;// 19 Swap of the short position. 
extern bool show_MODE_STARTING = true;// 20 Market starting date (usually used for futures). 
extern bool show_MODE_EXPIRATION = true;// 21 Market expiration date (usually used for futures). 
extern bool show_MODE_TRADEALLOWED = true;// 22 Trade is allowed for the symbol. 
extern bool show_MODE_MINLOT = true;// 23 Minimum permitted amount of a lot. 
extern bool show_MODE_LOTSTEP = true;// 24 Step for changing lots. 
extern bool show_MODE_MAXLOT = true;// 25 Maximum permitted amount of a lot. 
extern bool show_MODE_SWAPTYPE = true;// 26 Swap calculation method. 0 - in points; 1 - in the symbol base currency; 2 - by interest; 3 - in the margin currency. 
extern bool show_MODE_PROFITCALCMODE = true;// 27 Profit calculation mode. 0 - Forex; 1 - CFD; 2 - Futures. 
extern bool show_MODE_MARGINCALCMODE = true;// 28 Margin calculation mode. 0 - Forex; 1 - CFD; 2 - Futures; 3 - CFD for indices. 
extern bool show_MODE_MARGININIT = true;// 29 Initial margin requirements for 1 lot. 
extern bool show_MODE_MARGINMAINTENANCE = true;// 30 Margin to maintain open positions calculated for 1 lot. 
extern bool show_MODE_MARGINHEDGED = true;// 31 Hedged margin calculated for 1 lot. 
extern bool show_MODE_MARGINREQUIRED = true;// 32 Free margin required to open 1 lot for buying. 
extern bool show_MODE_FREEZELEVEL = true;// 33 Order freeze level in points. If the execution price lies within the range defined by the freeze level, the order cannot be modified, cancelled or closed. 
*/

// Posunu do rohu
// 0 - Levy nahore
// 1 - Pravy nahore
// 2 - Levy dole
// 3 - Pravy dole
//#define ROH_HORE_LEVO 0
//#define ROH_HORE_PRAVO 1
//#define ROH_DULE_LEVO 2
//#define ROH_DULE_PRAVO 3

/**********************************************************************
funkce pro práci s infoBoxem
**********************************************************************/

/**
* vytvoøí informaèní box
*
*/

void MarketInfoList() {
   
   int colSize[] = {8,10,20};
   string colHead[] = {"parametr","hodnota","popis"};
   
   /*string tableHeader = formatText2Cell(colHead[0], colSize[0])
                        + formatText2Cell(colHead[1], colSize[1])
                        + formatText2Cell(colHead[2], colSize[2]);
   */                    
   string row = "";
   
   int move = 16;

   int i;
   //LabelCreate("MarketInfoBox", 5, 20, ROH_HORE_PRAVO, tableHeader, InfoboxFontSize, Yellow);

   for(i = 0; i < 35; i++) {
   
      row = tl_getMarketInfoName(i);
      if(row == UNKNOWN_NAME) {
         continue;
      }
   
      /*row = formatText2Cell(tl_getMarketInfoName(i), colSize[0]) +
              formatText2Cell(MarketInfo(Symbol(), i), colSize[1]) +
              formatText2Cell(tl_getMarketInfoDescription(i), colSize[2]);
              */
      row = row + " = " + MarketInfo(Symbol(), i) + " // " + tl_getMarketInfoDescription(i);
      Print(i + " " + row);
      //LabelCreate(tl_getMarketInfoName(i), 5, 40 + i * move, ROH_HORE_PRAVO, row, InfoboxFontSize, DarkGray);
   }
}

 
 string tl_getMarketInfoName(int i) {
 
   switch(i) {
      case MODE_LOW:
         return("MODE_LOW");
      case MODE_HIGH:
         return("MODE_HIGH");
      case MODE_TIME:
         return("MODE_TIME");
      case MODE_BID:
         return("MODE_BID");
      case MODE_ASK:
         return("MODE_ASK");
      case MODE_POINT:
         return("MODE_POINT");
      case MODE_DIGITS:
         return("MODE_DIGITS");
      case MODE_SPREAD:
         return("MODE_SPREAD");
      case MODE_STOPLEVEL:
         return("MODE_STOPLEVEL");
      case MODE_LOTSIZE:
         return("MODE_LOTSIZE");
      case MODE_TICKVALUE:
         return("MODE_TICKVALUE");
      case MODE_TICKSIZE:
         return("MODE_TICKSIZE");        
      case MODE_SWAPLONG:
         return("MODE_SWAPLONG");
      case MODE_SWAPSHORT:
         return("MODE_SWAPSHORT");
      case MODE_STARTING:
         return("MODE_STARTING");
      case MODE_EXPIRATION:
         return("MODE_EXPIRATION");
      case MODE_TRADEALLOWED:
         return("MODE_TRADEALLOWED");
      case MODE_MINLOT:
         return("MODE_MINLOT");
      case MODE_LOTSTEP:
         return("MODE_LOTSTEP");
      case MODE_MAXLOT:
         return("MODE_MAXLOT");
      case MODE_SWAPTYPE:
         return("MODE_SWAPTYPE");
      case MODE_PROFITCALCMODE:
         return("MODE_PROFITCALCMODE");
      case MODE_MARGINCALCMODE:
         return("MODE_MARGINCALCMODE");
      case MODE_MARGININIT:
         return("MODE_MARGININIT");        
      case MODE_MARGINMAINTENANCE:
         return("MODE_MARGINMAINTENANCE");
      case MODE_MARGINHEDGED:
         return("MODE_MARGINHEDGED");
      case MODE_MARGINREQUIRED:
         return("MODE_MARGINREQUIRED");
      case MODE_FREEZELEVEL:
         return("MODE_FREEZELEVEL");           
      default:
         return(UNKNOWN_NAME);
   }
 }
 
string tl_getMarketInfoDescription(int i) {

 
    switch(i) {
      case MODE_LOW:
         return("Low day price.");
      case MODE_HIGH:
         return("High day price.");
      case MODE_TIME:
         return("The last incoming tick time (last known server time).");
      case MODE_BID:
         return("Last incoming bid price. For the current symbol, it is stored in the predefined variable Bid.");
      case MODE_ASK:
         return("Last incoming ask price. For the current symbol, it is stored in the predefined variable Ask.");
      case MODE_POINT:
         return("Point size in the quote currency. For the current symbol, it is stored in the predefined variable Point.");
      case MODE_DIGITS:
         return("Count of digits after decimal point in the symbol prices. For the current symbol, it is stored in the predefined variable Digits.");
      case MODE_SPREAD:
         return("Spread value in points.");
      case MODE_STOPLEVEL:
         return("Stop level in points.");
      case MODE_LOTSIZE:
         return("Lot size in the base currency.");
      case MODE_TICKVALUE:
         return("Tick value in the deposit currency.");
      case MODE_TICKSIZE:
         return("Tick size in the quote currency.");        
      case MODE_SWAPLONG:
         return("Swap of the long position.");
      case MODE_SWAPSHORT:
         return("Swap of the short position.");
      case MODE_STARTING:
         return("Market starting date (usually used for futures).");
      case MODE_EXPIRATION:
         return("Market expiration date (usually used for futures).");
      case MODE_TRADEALLOWED:
         return("Trade is allowed for the symbol.");
      case MODE_MINLOT:
         return("Minimum permitted amount of a lot.");
      case MODE_LOTSTEP:
         return("Step for changing lots.");
      case MODE_MAXLOT:
         return("Maximum permitted amount of a lot.");
      case MODE_SWAPTYPE:
         return("Swap calculation method. 0 - in points; 1 - in the symbol base currency; 2 - by interest; 3 - in the margin currency.");
      case MODE_PROFITCALCMODE:
         return("Profit calculation mode. 0 - Forex; 1 - CFD; 2 - Futures.");
      case MODE_MARGINCALCMODE:
         return("Margin calculation mode. 0 - Forex; 1 - CFD; 2 - Futures; 3 - CFD for indices.");
      case MODE_MARGININIT:
         return("Initial margin requirements for 1 lot.");        
      case MODE_MARGINMAINTENANCE:
         return("Margin to maintain open positions calculated for 1 lot.");
      case MODE_MARGINHEDGED:
         return("Hedged margin calculated for 1 lot.");
      case MODE_MARGINREQUIRED:
         return("Free margin required to open 1 lot for buying.");
      case MODE_FREEZELEVEL:
         return("Order freeze level in points. If the execution price lies within the range defined by the freeze level, the order cannot be modified, cancelled or closed.");           
      default:
         return(UNKNOWN_DESCRIPTION);
   }
 }