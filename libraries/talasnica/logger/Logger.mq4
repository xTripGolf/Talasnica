//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import "talasnica/session/Session.ex4"
   string talasnica_session_getId();
   string talasnica_session_getEnv();
#import

/*****************************************
loging
******************************************/

/**
* zapíše øetìzec do logovacího souboru
*/
 
 int talasnica_logger_log(string str, int errorLevel = 0)
{
   
   /*if(debug){
      Print(str);
      return(0);
   }*/

   int handle;
 
   handle = FileOpen(talasnica_logger_getFileName(), FILE_CSV|FILE_WRITE|FILE_READ, ';');
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

/**
* vrací cestu k log souboru
*
*/

string talasnica_logger_getFileName () {
   return (AccountName() + "/" + talasnica_session_getId() + "_" + Symbol() + "_ "+ Year() + "-" + Month() + "-" + Day() + ".log");
}

/**
* aktuální èas jako øetìzec
*/

string tl_Vcil() {
   return (Symbol() + " at " + TimeToStr(TimeCurrent(),TIME_DATE|TIME_SECONDS));
}


