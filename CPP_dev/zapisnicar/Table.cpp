#include "stdafx.h"
#include "Table.h"

using namespace std;

Zapisnicar::Table::Table(void){
	isColumn = false;
	column = headMap.begin();
}

Zapisnicar::Table::~Table(void){

}

void Zapisnicar::Table::addColumn(string text, int width)
{
	headMap.insert(std::make_pair(text,width));
}

void Zapisnicar::Table::addColumn(char * text, int width)
{
	string s(text);
	Zapisnicar::Table::addColumn(s, width);
}

string Zapisnicar::Table::head(void) {
column = headMap.begin();
	stringstream proud(ios_base::out);

	Zapisnicar::Table::HeadMap::iterator it;
	for(it = headMap.begin(); it != headMap.end(); it++) {
		proud << setw(it->second) << it->first;
	}

	proud << endl;

	return proud.str();
	
}

/*string Zapisnicar::Table::format(void) {
	*stream << "ZAPISNICAR void upravuje";
	return string("");
}*/

string Zapisnicar::Table::format(ostream &os) {
	//stream = &os;
	//*stream << "ZAPISNICAR upravuje";

	if(isColumn) {
		column = headMap.begin();
		isColumn = true;
	}

	os << setw(column->second);

	column++;
	if(column == headMap.end()) {
		column = headMap.begin();
	}

	return string("");
}