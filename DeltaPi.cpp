#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
   	lcd.clear();
	lcd.setAutoscroll(hd44780::HSCROLL_LINE);	

	retrieveSQL(entries);
	entries.erase(0);
	
	/*string str;
	str = entries.find(10993472)->second.getFirstName();
	
	char buf[256];	
	sprintf(buf, "%s\n", str.c_str());
	
	lcd.move(1,0);
	printfl(buf, lcd);
	
	str = entries.find(10993472)->second.getLastName().c_str();
	lcd.move(10,1);
	printfl(buf, lcd);*/

	string input;
	int card = 0;

	do{
		//printfl("Scan card: ", lcd);
		//dev.setCursor(hd44780::CURSOR_SOLID | hd44780::CURSOR_BLINKING);
		scanCard(entries, card, lcd);
		time::sleep(5);
		if (card > 10){
			printInfo(entries, card, lcd);
		}
		time::sleep(5);


	}while (card != -1);
	lcd.clear();
	return 0;
}
