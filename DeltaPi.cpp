#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
	
	retrieveSQL(entries);
	entries.erase(0);
	
	char strbuf[256];
	
	sprintf(strbuf, "%s", entries.find(10993472)->second.getNameFirstLast());
	printfl(strbuf, &lcd);


	return 0;
}
