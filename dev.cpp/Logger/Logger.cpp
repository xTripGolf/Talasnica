
#include "Logger.h"

Logger::Log log("talasnica.log");
Logger::Log err("talasnica-err.log");

/*Logger::Log::Log(void)
{
}*/

Logger::Log::Log(char *fname)
{
	out.open(fname);
}

Logger::Log::~Log(void)
{
	out.close();
}
