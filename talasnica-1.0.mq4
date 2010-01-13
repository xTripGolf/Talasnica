//+------------------------------------------------------------------+
//|                                                    talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

#include <talasnica.inc-1.0.mqh>

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import "talasnica.lib-1.0.ex4"
   bool tl_setLots(double lots);
  // bool tl_setProfit(double profit = 0);
   string tl_Id();
   string tl_Comment();
   string tl_Vcil();
  //string tl_JournalFileName();
   int tl_OrderSend (int type, double volume, double price, double stoploss=0, double takeprofit=0, int magic = 0);
   bool tl_OrderModify (double price, double stoploss = 0, double takeprofit = 0);
   bool tl_OrderSelect(int type, int index);
   bool tl_OrderClose ();
   int tl_OrderTicket();
   double tl_OrderProfitSwap();
   bool tl_OrderCnt();
   double tl_getProfit (int type, int index);
   double tl_getTicket (int type, int index);
   int tl_C(int type);
   double tl_V(int type);
  // double tl_P(int type);
   double tl_Sw(int type);
   double tl_E(int type);
   double tl_PSw(int type);
   string tl_OrderName(int type);
   int tl_Zamceno();
   int tl_Otevreno();
   int tl_Previs();
   double tl_OrderTakeProfit();
   double tl_OrderOpenPrice();
   double tl_MedziTaure (double enter, int mezera);
   double tl_MedziMedvede (double enter, int mezera);
   double tl_OrderStopLoss();
   double tl_Pips2Money(int par);
   double tl_Money2Pips(int par);
   int tl_Log(string str, int errorLevel = 0);
#import

/**********************************************************************

***********************************************************************/

/**
* konstanty pro definici názvu vykreslovaných objektù
*
*/
#define INFOBOX_TABLEHEADER "header"

#define INFOBOX_STOPS "koliko èaka stopu" // poèet odložených obchodù
#define INFOBOX_LIMITS "koliko èaka limitek" // poèet odložených obchodù


#define INFOBOX_CELLSIZE_NAME 6
#define INFOBOX_CELLSIZE_COUNT 5
#define INFOBOX_CELLSIZE_VOLUME 6
#define INFOBOX_CELLSIZE_PRICE 8
#define INFOBOX_CELLSIZE_PROFIT 10

#define INFOBOX_CELLSIZE_TICKET 8

int InfoboxRows[]; // øádky, které se zobrazí v infoboxu

// Posunu do rohu
// 0 - Levy nahore
// 1 - Pravy nahore
// 2 - Levy dole
// 3 - Pravy dole
#define ROH_HORE_LEVO 0
#define ROH_HORE_PRAVO 1
#define ROH_DULE_LEVO 2
#define ROH_DULE_PRAVO 3

// **************** EXTERN PARAMETERS

//
extern int BerProfitPips = 10;

extern double StartLots=0.1; // poèáteèní volume a pøírustek lotù

// nastaveni
extern int OkvirMreze = 10; // šíøka pásu v bodech = poèet pozic na každou stranu
extern int OdstojanjeZaTaurus = 10; // oblast okolo aktuální ceny Ask/Bid, kde nelze zadávat odložené obchody
extern int OdstojanjeZaMedved = 10; // oblast okolo aktuální ceny Ask/Bid, kde nelze zadávat odložené obchody
extern int OkoMrezeZaTaurus = 14; // rozestup mezi odloženými obchody v bodech
extern int OkoMrezeZaMedved = 14; // rozestup mezi odloženými obchody v bodech
extern int ZagusnikZaTaurus = 13; // minimální vydálenost stop obchodù od otevøených obchodù
extern int ZagusnikZaMedved = 13; // minimální vydálenost stop obchodù od otevøených obchodù

// to delete
//extern int Slippage=3;

extern int Length=4;            //length of range for determining high/low

// odesílání informaèních emailù
extern int MajlulPoPipsech = 50;
double Odmajlovano = 0;

extern int InfoboxFontSize = 10;
extern string InfoboxFontName = "Courier";
// **************** END OF EXTERN PARAMETERS

/**
* pomocné promìnné
*
* èasto použiavné, proto se definují již tu
*/
double _takeprofit, _openprice; //, _stoploss;

extern int ZvonitiZaOutput = 10;

extern bool autoPosun = false, autoBerba = false;
//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
  {
    
//---- 
   Print("******************************");
   Print("*** TALASNICA STARTUJE ***");
   Print("******************************");
   Print("*** FUNCTION INIT ***");

   // nastavíme velikost lotù pro nové obchody
   
   tl_setLots(StartLots);
   
   tl_Log("*** TALASNICA STARTUJE ***", LOG_INIT);
   
   ObjectsDeleteAll(-1, OBJ_LABEL);
   ArrayResize(InfoboxRows, 8);
   InfoboxRows[0] = OP_BUY;
   InfoboxRows[1] = OP_SELL;
   InfoboxRows[2] = OP_OPENED;
   InfoboxRows[3] = OP_PREMOC;
   InfoboxRows[4] = OP_PROFIT;
   InfoboxRows[5] = OP_LOSS;
   InfoboxRows[6] = OP_SVETAURUS;
   InfoboxRows[7] = OP_SVEMEDVED;
   
   CreateInfoBox();
   
   Print("Obchodovaná mìna: Order Symbol = ", Symbol());
   
  /* if (Period() != xronos)
    {
    Print("Nastavena nesprávná perioda pracovního grafu.");
    Print("Perioda aktuálního grafu je ", Period(), ", požadovaná perioda je ", xronos);
    return (-1);
    }
   else {
   Print("Èasová perioda grafu: Period = ", Period());
   }*/
 
   // nezùstal zaseknutý globální InTrade ?
   // Jednou se mi to stalo, nešly obchody a já nevìdìl co s tím
   // Tohle to øeší
 
   if (GlobalVariableCheck("InTrade")) {
      GlobalVariableDel("InTrade");   // clear lock indicator
   }
 
  if (MarketInfo(Symbol( ), MODE_STOPLEVEL) > OdstojanjeZaTaurus) {
      OdstojanjeZaTaurus = MarketInfo(Symbol( ) , MODE_STOPLEVEL);
      Print("oprava hodnoty OdstojanjeZaTaurus = ", OdstojanjeZaTaurus);
   }
 
  if (MarketInfo(Symbol( ), MODE_STOPLEVEL) > OdstojanjeZaMedved) {
      OdstojanjeZaMedved = MarketInfo(Symbol( ) , MODE_STOPLEVEL);
      Print("oprava hodnoty OdstojanjeZaMedved = ", OdstojanjeZaMedved);
   }
 
   Print("*** END OF FUNCTION INIT ***");
//----
   
   return(1);
  }
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit()
  {
//---- 

   Print("*** FUNCTION DEINIT ***");

//----
   Print("******************************");
   Print("*** TALASNICA GOTOVO ***");
   Print("******************************");
   tl_Log("*** TALASNICA GOTOVO ***", LOG_INIT);
   return(0);
  }

//+------------------------------------------------------------------+
//| expert start function                                            |
//+------------------------------------------------------------------+
int start()
  {
//----
  
   // pøepoèítáme obchody
   tl_OrderCnt();
   
   // vytvoøíme informaèní box
   WriteInfo();
  
   if(autoBerba) {
      zadajBerbu();
   }
    
   if(MajlulPoPipsech > 0 && MathAbs(Ask - Odmajlovano) > MajlulPoPipsech * Point) {
      SendMail("kurz " + Symbol(), tl_Vcil() + " Ask = " + DoubleToStr(Ask, Digits) + " equity " + DoubleToStr(AccountEquity(), 2) + " balance " + DoubleToStr(AccountBalance(), 2)  + " profit " + DoubleToStr(AccountProfit(), 2) 
               + " otvoreno " + DoubleToStr(tl_V(OP_OPENED), 2));
      Odmajlovano = Ask;
   }
    
   // Posuneme odložené obchody
   if(autoPosun) {
      Posun();
   }
   
   if(tl_Zamceno() > 0) {
      double zvoniti = NormalizeDouble(ZvonitiZaOutput * Point, Digits);
      if(NormalizeDouble(MathAbs((Ask + Bid)/2 - tl_E(OP_SVETAURUS)), Digits) < zvoniti || NormalizeDouble(MathAbs((Ask + Bid)/2 - tl_E(OP_SVEMEDVED)), Digits) < zvoniti) {
         //PlaySound("alert.wav");
      }
     
   }
   
/*
   if(tl_Zamceno() > 0) {
      double zamcenaNejvetsiZtrata = tl_getProfit(OP_BUY, tl_C(OP_BUY) - 1) + tl_getProfit(OP_SELL, tl_C(OP_SELL) - 1);
      double volnyProfit = tl_PSw(OP_PREMOC);
      
      if(zamcenaNejvetsiZtrata + volnyProfit > tl_Pips2Money(BerProfitPips) * StartLots) {
         // zavreme pøevis
         int previs = tl_Previs();
         double profit = 0;
         int i;
         
         if(previs > 0) {
            Print("PREVIS " + previs);
            for(i = 0; i < previs; i++) {
               if(tl_OrderSelect(OP_BUY, i)) {
                  if(tl_OrderProfitSwap() > 0) {
                     profit = tl_OrderProfitSwap();
                     tl_OrderClose();
                     Print(tl_OrderTicket() + " premoc za " + tl_OrderProfitSwap());
                  }
               }
            }
         }
   
          if(previs < 0) {
            Print("PREVIS " + previs);
            previs = -1 * previs;
            for(i = 0; i < previs; i++) {
               if(tl_OrderSelect(OP_SELL, i)) {
                  if(tl_OrderProfitSwap() > 0) {
                     profit += tl_OrderProfitSwap();
                     tl_OrderClose();
                     Print(tl_OrderTicket() + " premoc za " + tl_OrderProfitSwap());
                  }
               }
            }
         }
         
         // a take onen zámek
        // if(profit + zamcenaNejvetsiZtrata > 0) {
            if(tl_OrderSelect(OP_BUY, tl_C(OP_BUY) - 1)) {
              profit += tl_OrderProfitSwap();
              tl_OrderClose();
              Print(tl_OrderTicket() + " buy zámek za " + tl_OrderProfitSwap());
            }
            if(tl_OrderSelect(OP_SELL, tl_C(OP_SELL) - 1)) {
              profit += tl_OrderProfitSwap();
              tl_OrderClose();
              Print(tl_OrderTicket() + " sell zámek za " + tl_OrderProfitSwap());
            }
         //}

         Print("zavøení zámku " + profit);
         if(profit < 0) {
           SendMail("zavøení zámku do mínusu ", tl_Vcil() + " zavøeno za = " + DoubleToStr(profit, 2));  
         }
   }    
   }*/
 
   return(1);
  }
//+------------------------------------------------------------------+
//+------------------------------------------------------------------+
//| expert users functions                                            |
//+------------------------------------------------------------------+


/****************************************************************
nastavi jednotny Output
****************************************************************/

int zadajBerbu () {

int i;

/**********************************
   žádné pozice
**********************************/
   if(tl_Otevreno() == 0) {
      return(0);
   }

/**********************************
   pozice jsou jen v jednom smìru
**********************************/
   // a to v bull
/*   if(tl_C(OP_BUY) > 0 && tl_C(OP_SELL) == 0) {
     for(i = 0; i < tl_C(OP_BUY); i++) {
         if(tl_OrderSelect(OP_BUY, i)) {
            tl_OrderModify(tl_OrderOpenPrice(), 0, tl_OrderOpenPrice() + BerProfitPips * Point);  
         }
     }
     return(1); 
   }
   // a nebo bear
   if(tl_C(OP_SELL) > 0 && tl_C(OP_BUY) == 0) {
     for(i = 0; i < tl_C(OP_SELL); i++) {
         if(tl_OrderSelect(OP_SELL, i)) {
            tl_OrderModify(tl_OrderOpenPrice(), 0, tl_OrderOpenPrice() - BerProfitPips * Point);  
         }
     }
     return(2); 
   }
*/
/**********************************
   existují zámky, ale jedna strana má pøevis
**********************************/

   double ttp = 0, tsl = 0, mtp = 0, msl = 0;
   
   double _saveProfit = BerProfitPips;
   if(tl_Sw(OP_OPENED) < 0) {
      _saveProfit -= tl_Money2Pips(tl_Sw(OP_OPENED)) / StartLots;
   } 
   _saveProfit *= Point;
   _saveProfit = NormalizeDouble(_saveProfit + Point, Digits);
 
   ttp = tl_E(OP_SVETAURUS) + _saveProfit / (tl_C(OP_SVETAURUS));
   msl = ttp + Ask - Bid;
   mtp = tl_E(OP_SVEMEDVED) + _saveProfit / (tl_C(OP_SVEMEDVED));
   tsl = mtp - Ask + Bid;
 
  for(i = 0; i < tl_Otevreno(); i++) {
      if(tl_OrderSelect(OP_BUY, i)) {
         tl_OrderModify(tl_OrderOpenPrice(), tsl, ttp);
      }
      
      if(tl_OrderSelect(OP_SELL, i)) {
         tl_OrderModify(tl_OrderOpenPrice(), msl, mtp);
      }
  }
  
  int berbaLevel;
  
  berbaLevel = tl_C(OP_SVETAURUS) - tl_C(OP_OPENED);
  
  for(i = 0; i < tl_C(OP_BUYSTOP); i++) {
      if(tl_OrderSelect(OP_BUYSTOP, i)) {
         if(i <= berbaLevel) {
            tl_OrderModify(tl_OrderOpenPrice(), tsl, ttp);
         }
         else  {
            tl_OrderModify(tl_OrderOpenPrice(), 0, tl_OrderOpenPrice() + BerProfitPips * Point);
         }
      }
  }
  
  berbaLevel = -1 * (tl_C(OP_SVEMEDVED) - tl_C(OP_OPENED));
  
  for(i = 0; i < tl_C(OP_SELLSTOP); i++) {
      if(tl_OrderSelect(OP_SELLSTOP, i)) {
         if(i <= berbaLevel) {
            tl_OrderModify(tl_OrderOpenPrice(), msl, mtp);
         }
         else {
            tl_OrderModify(tl_OrderOpenPrice(), 0, tl_OrderOpenPrice() - BerProfitPips * Point);
         }
      }
  }
  
}

/****************************************************************
posune odložené obchody
****************************************************************/

void Posun() {
  
  //int rozestupObchodu = RozestupObchodu + (Ask - Bid) / Point;
  //int rozestupObchodu = RozestupObchodu + MarketInfo(Symbol(), MODE_SPREAD);
  
  // hranice vstupu
  double EntryLong   = iHigh(NULL,Period(),iHighest(NULL,Period(),MODE_HIGH,Length,0));
  double EntryShort  = iLow (NULL,Period(),iLowest (NULL,Period(),MODE_LOW, Length,0));
 
  // dle BB
  
  //double EntryLong = iBands(NULL, 0, 21, 2, 0, PRICE_HIGH, MODE_UPPER, 0);
  //double EntryShort = iBands(NULL, 0, 21, 2, 0, PRICE_LOW, MODE_LOWER, 0);
  
  EntryLong += OdstojanjeZaTaurus * Point;
  EntryShort -= OdstojanjeZaMedved * Point;
 
  EntryLong      = NormalizeDouble(MathMax(EntryLong, Ask + OdstojanjeZaTaurus * Point), Digits);
  EntryShort     = NormalizeDouble(MathMin(EntryShort, Bid - OdstojanjeZaMedved * Point), Digits);

  double profitPrice = 0;
  int ticket;

  double bullProfit = 0, bearProfit = 0;

  int _c_buystop = tl_C(OP_BUYSTOP);
  int _c_sellstop = tl_C(OP_SELLSTOP);
 // int spreadInPoint = MarketInfo(Symbol(), MODE_SPREAD) * Point;

  for (int i = 0; i < OkvirMreze; i++) {
   //Print("POSUN " + i);
   //Print("EntryLong " + EntryLong);
   //Print("EntryShort " + EntryShort);
   // aby se nedublovalo, nehromadilo
   EntryLong = tl_MedziTaure(EntryLong, ZagusnikZaTaurus);// + spreadInPoint;
   EntryShort = tl_MedziMedvede(EntryShort, ZagusnikZaMedved);// - spreadInPoint;


   /* BULL */
  
    if(i < _c_buystop) {
      if(tl_OrderSelect(OP_BUYSTOP, i)) {
         _takeprofit = tl_OrderTakeProfit();
         _openprice = tl_OrderOpenPrice();
  
         // posun
         if (_openprice > EntryLong) {      
          if(_takeprofit > 0) {
            profitPrice = _takeprofit - _openprice + EntryLong;
          }
          else {
            profitPrice = 0;
          }
          Print("op from " + _openprice + " to " + EntryLong + " sl = " + tl_OrderStopLoss());
          tl_OrderModify(EntryLong, 0, profitPrice);
          Print("sl = " + tl_OrderStopLoss());
        } // end if _openprice > EntryLong
      } // end if select order
    } // end posun obchodu
    else {
      
      profitPrice = EntryLong + BerProfitPips * Point;
    
      ticket = tl_OrderSend(OP_BUYSTOP, StartLots, EntryLong, 0, profitPrice, 0);
      
      if(ticket < 0) {
       tl_Log("Error opening bull order at " + EntryLong + " error: " + ErrorDescription(GetLastError()), LOG_ERROR);
      }
      else {
        tl_Log("doplnìn bull stop ticket = " + ticket + " at price " + EntryLong, LOG_INFO);
      }
    } // end else - doplneni obchodu
    
    EntryLong += OkoMrezeZaTaurus * Point;
    
    /* BEAR */
    
    if(i < _c_sellstop) {
      if(tl_OrderSelect(OP_SELLSTOP, i)) {
         _takeprofit = tl_OrderTakeProfit();
         _openprice = tl_OrderOpenPrice();
  
         // posun
         if (_openprice < EntryShort) {      
           //Print("bull openprice move from " + _openprice + " to " + EntryLong);
          if(_takeprofit > 0) {
            profitPrice = _takeprofit - _openprice + EntryShort;
          }
          else {
            profitPrice = 0;
          }
          tl_OrderModify(EntryShort, 0, profitPrice);
        } // end if _openprice > EntryLong
      } // end if select order
    } // end posun obchodu
    else {
      profitPrice = EntryShort - BerProfitPips * Point;
    
      ticket = tl_OrderSend(OP_SELLSTOP, StartLots, EntryShort, 0, profitPrice, 0);
      
      if(ticket < 0) {
       tl_Log("Error opening bear order at " + EntryShort + " error: " + ErrorDescription(GetLastError()), LOG_ERROR);
      }
      else {
        tl_Log("doplnìn bear stop ticket = " + ticket + " at price " + EntryShort, LOG_INFO);
      }
    } // end else - doplneni obchodu
    
    EntryShort -= OkoMrezeZaMedved * Point;
  } // end for

}

/**********************************************************************
funkce pro práci s infoBoxem
**********************************************************************/
/**
* Funkce na vytvareni popisku na grafu
*/

void LabelCreate(string _LabelName, int _OsaX, int _OsaY, int _Roh = 2, string _Text = "", int _FontSize = 12, color _Color = Yellow)
{
   int _GetLastError;

   //Vytvorim objekt
   if ( !ObjectCreate( _LabelName, OBJ_LABEL, 0, 0,  0) ){
      _GetLastError = GetLastError();
      if ( _GetLastError != 4200 )
      {
         tl_Log( "LabelCreate() - ObjectCreate( \"" +  _LabelName + "\") - Error #" +  _GetLastError + " )", LOG_ERROR);
         return(-1);
      }
}

   // Posunu do rohu
   // 0 - Levy nahore
   // 1 - Pravy nahore
   // 2 - Levy dole
   // 3 - Pravy dole

   ObjectSet( _LabelName, OBJPROP_CORNER, _Roh );
   //Posun dle osy X
   ObjectSet( _LabelName, OBJPROP_XDISTANCE, _OsaX );
   //Posun dle osy Y
   ObjectSet( _LabelName, OBJPROP_YDISTANCE, _OsaY );
   //Nastavim Text a Barvu textu
   ObjectSetText (_LabelName, _Text , _FontSize, InfoboxFontName, _Color);
}

/**
* vytvoøí informaèní box
*
*/

void CreateInfoBox() {

   string tableHeader = formatText2Cell("type", INFOBOX_CELLSIZE_NAME)
                        + formatText2Cell("count", INFOBOX_CELLSIZE_COUNT)
                        + formatText2Cell("volume", INFOBOX_CELLSIZE_VOLUME)
                        + formatText2Cell("price", INFOBOX_CELLSIZE_PRICE)
                        + formatText2Cell("profit", INFOBOX_CELLSIZE_PROFIT);
   
   int move = 16;

   int i, index;
   LabelCreate(INFOBOX_TABLEHEADER, 5, 20, ROH_HORE_PRAVO, tableHeader, InfoboxFontSize, Yellow);

   for(i = 0; i < ArraySize(InfoboxRows); i++) {
      index = InfoboxRows[i];
      LabelCreate(tl_OrderName(index), 5, 40 + i * move, ROH_HORE_PRAVO, tl_OrderName(index), InfoboxFontSize, DarkGray);
   }
   
   LabelCreate(INFOBOX_STOPS, 5, 40 + i * move, ROH_HORE_PRAVO, INFOBOX_STOPS, InfoboxFontSize, DarkGray);
   i++;
   LabelCreate(INFOBOX_LIMITS, 5, 40 + i * move, ROH_HORE_PRAVO, INFOBOX_LIMITS, InfoboxFontSize, DarkGray);
   
}

/**
* vytvoøí textová pole pro seznam zámkù
*
*/

void CreateInfoBoxHedged() {
   //string tableHeader = formatText2Cell("bull") + formatText2Cell("bear") + formatText2Cell("price");
   int move = 18;
   
   // smazeme ty navic
   
   int i = tl_Zamceno();
   string name = "hedged_" + i;
   
   while (ObjectFind(name) >= 0) {
      ObjectDelete(name);
      i++;
      name = "hedged_" + i;
   }  
   
   // vytvorime ty potrebne
   
   for(i = 0; i < tl_Zamceno(); i++) {
      name = "hedged_" + i;
      if(ObjectFind(name) < 0) {
         LabelCreate(name, 5, 5 + i * move, ROH_DULE_LEVO, "#" + i, InfoboxFontSize, Yellow);
      } 
   }
}

/**
*
*
*
*
*
*/

void WriteInfo() {

   string label;
   
   label = "STOPS - još èaka " + tl_C(OP_BUYSTOP) + " gore " + tl_C(OP_SELLSTOP) + " dole ";
   ObjectSetText(INFOBOX_STOPS, label, InfoboxFontSize, InfoboxFontName, White);
   
   label = "LIMITS - još èaka " + tl_C(OP_BUYLIMIT) + " gore " + tl_C(OP_SELLLIMIT) + " dole ";
   ObjectSetText(INFOBOX_LIMITS, label, InfoboxFontSize, InfoboxFontName, White);

   double tickValue = MarketInfo(Symbol(), MODE_TICKVALUE);
   
   int index;
   
   color barva;
   
   for(int i = 0; i < ArraySize(InfoboxRows); i++) {
      index = InfoboxRows[i];
      label = formatText2Cell(tl_OrderName(index), INFOBOX_CELLSIZE_NAME) +
              formatText2Cell(tl_C(index), INFOBOX_CELLSIZE_COUNT) +
              formatText2Cell(DoubleToStr(tl_V(index), 2), INFOBOX_CELLSIZE_VOLUME) +
              formatText2Cell(DoubleToStr(tl_E(index), Digits), INFOBOX_CELLSIZE_PRICE) +
              formatText2Cell(DoubleToStr(tl_PSw(index), 2), INFOBOX_CELLSIZE_PROFIT);
      if (tl_C(index) == 0) {
         barva = DarkGray;
      }
      else {              
         if (tl_PSw(index) < 0) {
            barva = Magenta;
         }
         else if (tl_PSw(index) < BerProfitPips * tickValue * StartLots) {
            barva = Aqua;
         }
         else {
            barva = LawnGreen;
         }
      }
      ObjectSetText(tl_OrderName(index), label, InfoboxFontSize, InfoboxFontName, barva);
   }
  
   // hedged
   CreateInfoBoxHedged();
   i = 0;
   int bulls = tl_C(OP_BUY);
   int bears = tl_C(OP_SELL);
   int iBears, iBulls;
   string name = "hedged_" + i;
   double profitZamku;
   while (ObjectFind(name) >= 0) {
      iBears = bears - i - 1;
      iBulls = bulls - i - 1;
      profitZamku = tl_getProfit(OP_BUY, iBulls) + tl_getProfit(OP_SELL, iBears);
      label = formatText2Cell(DoubleToStr(tl_getTicket(OP_BUY, iBulls), 0), INFOBOX_CELLSIZE_TICKET) +
              formatText2Cell(DoubleToStr(tl_getTicket(OP_SELL, iBears), 0), INFOBOX_CELLSIZE_TICKET) +
              formatText2Cell(DoubleToStr(profitZamku, 2), INFOBOX_CELLSIZE_PROFIT);
      if(profitZamku > 0) {
         barva = LawnGreen;
      }
      else {
         barva = Yellow;
      }
      ObjectSetText(name, label, InfoboxFontSize, InfoboxFontName, barva);
      i++;
      name = "hedged_" + i;
   }
 }

/**
* naformátuje text do tabulky
*
*/

string formatText2Cell(string text, int cellSize = 12) {
   
   int strLen = StringLen(text);
   
   if(strLen > cellSize) {
      text = StringSubstr(text, 0, cellSize);
      return(text);
   }
   else {
      string space;
      for(int i = 0; i < cellSize - strLen; i++) {
         space = space + " ";
      }
      return("|" + space + text );
   }
   
}




