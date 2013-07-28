#include "header.h"

map<const int, Entry> entries;
//Entry person;

int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
   	lcd.clear();
	lcd.setAutoscroll(hd44780::HSCROLL_LINE | hd44780::VSCROLL);	

	retrieveSQL(entries);
	entries.erase(0);
	
	int card = 0;

	do{
		scanCard(entries, card, lcd);
		if (card > 10){
			printInfo(entries, card, lcd);
			transaction(entries, card, lcd);
		}
	}while (card != -1);
	lcd.clear();
	return 0;
}
