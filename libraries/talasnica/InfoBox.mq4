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
#import "talasnica/Log.ex4"
   string tl_Log(string str, int errorLevel = 0);
#import

/**********************************************************************

***********************************************************************/

//extern int InfoboxFontSize = 10;
extern string InfoboxFontName = "Courier";

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


