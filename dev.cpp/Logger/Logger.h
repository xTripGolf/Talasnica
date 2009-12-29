#ifndef _LOG_H_
#define _LOG_H_

#define eoln "\n"
#define logERROR "ERROR : "<<__FILE__<<":"<<(long int)__LINE__
#include <stdlib.h>
#include <stdio.h>

//#define _LOG_OFF_

struct Log{
	FILE *f;
	Log(char *fname)
	{
		//f=fopen(fname,"wt");
		errno_t err = fopen_s( &f, fname,"wt");
		
//		fprintf(f,"=========== LOG start ===========\n");
	}

	Log()
	{
		f=stdout;
//		fprintf(f,"=========== LOG start ===========\n");
	}

  Log& operator << (char *txt)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%s",txt);
		fflush(f);
#endif
		return *this;
	}

  Log& operator << (char c)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%c",c);
		fflush(f);
#endif
		return *this;
	}

  Log& operator << (int num)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%d",num);
		fflush(f);
#endif
		return *this;
	}

  Log& operator << (unsigned int num)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%d",num);
		fflush(f);
#endif
		return *this;
	}


  Log& operator << (float num)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%7.3f",num);
		fflush(f);
#endif
		return *this;
	}

  Log& operator << (double num)
	{
#ifndef _LOG_OFF_
		fprintf(f,"%f",(float)num);
		fflush(f);
#endif
		return *this;
	}
	
/*
  Log& operator << (Vector3f &v)
	{
		fprintf(f,"%3.6f %3.6f %3.6f ",v.x,v.y,v.z);
		fflush(f);
		return *this;
	}
*/
	~Log()
	{
//		fprintf(f,"=========== LOG end ===========\n");
		fclose(f);
	}

};

extern Log *infolog;


#ifndef INFOLOG
#define INFOLOG *infolog
#endif

#define LOGSTART infolog = new Log("log.txt");
#define LOGSTOP  delete infolog;

#endif