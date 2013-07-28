#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
   	lcd.clear();
	
	retrieveSQL(entries);
	entries.erase(0);
	
	string str = entries.find(10993472)->second.getFirstName().c_str();
	
	//sprintf(strbuf, "%s", buf);
	lcd.move(5,0);
	printfl(str, lcd);
	
	string str = entries.find(10993472)->second.getLastName().c_str();
	lcd.move(5,1);
	printfl(str, lcd);

	return 0;
}
