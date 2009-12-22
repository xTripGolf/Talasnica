//+------------------------------------------------------------------+
//|                                                 talasnica_EA.mq4 |
//|                            Copyright © 2005-2009, MITHRADES a.s. |
//|                                           http://forex.xTrip.net |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005-2009, MITHRADES a.s."
#property link      "http://forex.xTrip.net"

#include <talasnica.mqh>

#import "stdlib.ex4"
   string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import "talasnica/session/Session.ex4"
   void talasnica_session_setId(string id);
   string talasnica_session_getId();
   string talasnica_session_getComment();
   void talasnica_session_setEnv(int environment);
#import

extern bool development_mode = true;

//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
  {
//----

   string name = "talasnica EA";

   Print("******************************");
   Print("*** TALASNICA STARTUJE ***");
   Print("*** " + name + " ***");
   Print("******************************");

   talasnica_session_setId(name);
   if(development_mode) {
      talasnica_session_setEnv(ENVIRONMENT_DEVELOPMENT);
   }
   
   Comment(talasnica_session_getComment());
   
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit()
  {
//----
   Print("******************************");
   Print("*** " + talasnica_session_getId() + " ***");
   Print("*** TALASNICA GOTOVO ***");
   Print("******************************");
   return(0);   
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| expert start function                                            |
//+------------------------------------------------------------------+
int start()
  {
//----
   
//----
   return(0);
  }
//+------------------------------------------------------------------+