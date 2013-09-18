#include "header.h"

map<const int, Entry> entries;


int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
	lcd.setAutoscroll(hd44780::HSCROLL_LINE | hd44780::VSCROLL);
	
	io.setup(23, rpihw::gpio::OUTPUT);
	io.write(23, rpihw::gpio::HIGH); bool backlight = true;

	uint8_t blank[8]		= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	lcd.defChar(hd44780::CCHAR2, blank);

	retrieveSQL(entries, lcd);
	entries.erase(0);
	
	int card = 0;
	
	lcd.move(0,2);
	printfl("DeltaPi ver. 0.7.1",lcd);
	
	do{
		retrieveSQL(entries, lcd);
		scanCard(entries, card, lcd);
		if (card > 10){
			printInfo(entries, card, lcd);
			transaction(entries, card, lcd);
		}
		else if (card == 0){
			printHelp(lcd);
		}else if (card == 1){
			printSummary(entries, lcd);
		} else if (card == 2){
			lcd.clear();
			lcd.move(0,1);
			printfl("Retrieving database");
			retrieveSQL(entries, lcd);	
		} else if (card == 4){
			printTime(lcd);
		} else if (card == 6){
			printLastCoffee(lcd);
		} else if (card == 9){
			changeBacklight(&backlight);
		}
	}while (card != -1);
	lcd.clear();
	printfl("  Closing DeltaPi\n\n      Goodbye!", lcd);
	
	return 0;
}
