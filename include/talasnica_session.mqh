//+------------------------------------------------------------------+
//|                                            talasnica_session.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
/**
konstanty pro oznaèení prostøedí
**/
#define ENVIRONMENT_PRODUCTION 2
#define ENVIRONMENT_DEVELOPMENT 4
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//| EX4 imports                                                      |
//+------------------------------------------------------------------+
#import "talasnica/session/Session.ex4"
   void talasnica_session_setId(string id);
   string talasnica_session_getId();
   string talasnica_session_getComment();
   void talasnica_session_setEnv(int environment);
   int talasnica_session_getEnv();
   string talasnica_session_getEnvName();
#import
//+------------------------------------------------------------------+




