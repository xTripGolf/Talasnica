// Table.h

#pragma once

#include <cstdio>
#include <iostream>
//#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

namespace Zapisnicar {

	class Table
	{
		typedef std::map<string, int> HeadMap;
		private:
			HeadMap headMap;
			HeadMap::iterator column;
			bool isColumn;
			//ostream * stream;
		public:
			Table(void);
			~Table(void);
			void addColumn(string text, int width);
			void addColumn(char * text, int width);
			string head(void);
			//string format(void);
			string format(ostream &os);
	};
}
