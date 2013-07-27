#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
	
	retrieveSQL(entries);
	entries.erase(0);
	
	char strbuf[256];
	
	string buf = entries.find(10993472)->second.getFirstName();
	
	sprintf(strbuf, "%s", buf);
	printfl(strbuf, lcd);


	return 0;
}
