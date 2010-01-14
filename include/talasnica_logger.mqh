//+------------------------------------------------------------------+
//|                                             talasnica_logger.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
/**
* konstanty pro úroveò výpisu logování
* @todo dodìlat
*/

#define LOG_INIT 2
#define LOG_ERROR 4
#define LOG_INFO 8
#define LOG_SCRIPT 16
#define LOG_ 0
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//| EX4 imports                                                      |
//+------------------------------------------------------------------+
#import "talasnica/logger/Logger.ex4"
   bool talasnica_logger_init(string environment, string id);
   int talasnica_logger_log(string str, int level);
   string talasnica_logger_getPath();
   /**
   * vypíše chybu jako label na obrazovku, velkým a výrazným písmem
   **/
   void talasnica_logger_err(string err);
#import
//+------------------------------------------------------------------+

