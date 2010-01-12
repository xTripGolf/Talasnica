//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

//#include "./../../../include/stdlib.mqh"
//#include "./../../../include/talasnica_dll.mqh"
//#include "./../../../include/talasnica_logger.mqh"
#include "./../../../include/talasnica_session.mqh"

#import "stdlib.ex4"
   //string ErrorDescription(int error_code);
   //int    RGB(int red_value, int green_value, int blue_value);
   //bool   CompareDoubles(double number1, double number2);
   //string DoubleToStrMorePrecision(double number, int precision);
   //string IntegerToHexString(int integer_number);
#import

string _id = "talasnica default id";
int _environment = ENVIRONMENT_PRODUCTION;

void talasnica_session_setId(string id) {
   Print("talasnica_session_setId(string id) id = " + id);
   _id = id;
   Print("set _id = " + _id);
}


/**
* id obchodního systému
*
*/

string talasnica_session_getId() {
   Print("talasnica_session_getId() return id = " + _id);
   return(_id);
}

/**
* komentáø pro oznaèení obchodù
*
*/

string talasnica_session_getComment() {
   return ("AOS »" + talasnica_session_getId() + "« bìží v prostøedí »" + talasnica_session_getEnvName() + "« spuštìno " + Day() + "." + Month() + "." + Year() + " " + TimeToStr(TimeCurrent(),/*TIME_DATE|*/TIME_SECONDS));
   //return (talasnica_session_getId() + " " + Symbol());
}

/****************************
ENVIRONMENT
****************************/

/**
* nastaví prostøedí obchodního systému
*
*/

void talasnica_session_setEnv(int environment) {
   switch(environment){
      case ENVIRONMENT_DEVELOPMENT:
         _environment = ENVIRONMENT_DEVELOPMENT;
         break;
      default:
         _environment = ENVIRONMENT_PRODUCTION;
   }
   
}


/**
* vrátí prostøedí obchodního systému
*
*/

int talasnica_session_getEnv() {
   return(_environment);
}

/**
* vrátí prostøedí obchodního systému
*
*/

string talasnica_session_getEnvName() {
    switch(_environment){
      case ENVIRONMENT_DEVELOPMENT:
         return("development");
      default:
         return("production");
   }
}