#include "header.h"




int main(int argc, char* argv[]){

	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
	lcd.setAutoscroll(hd44780::HSCROLL_LINE | hd44780::VSCROLL);
	
	rpihw::gpio io;
	io.setup(23, rpihw::gpio::OUTPUT);
	io.write(23, rpihw::gpio::HIGH); bool *backlight = new bool(true);

	uint8_t blank[8]		= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	lcd.defChar(hd44780::CCHAR2, blank);
	
	map<const int, Entry> entries;
	retrieveSQL(entries, lcd);
	entries.erase(0);
	
	int card = 0;
	
	lcd.move(0,2);
	printfl("DeltaPi ver. 0.7.7",lcd);
	
	do{
		moveAndClearLine(0,0,lcd);
		lcd.write("Retrieving database");
		retrieveSQL(entries, lcd);
		scanCard(entries, card, lcd);
		if (!(*backlight))
			changeBacklight(io, backlight, lcd);
		if (card > 10){
			printInfo(entries, card, lcd);
			transaction(entries, card, lcd);
		}
		else if (card == 0){
			printHelp(lcd);
		}else if (card == 1){
			printSummary(entries, lcd);
		} else if (card == 3){
			lcd.clear();
			lcd.move(0,1);
			printfl("Retrieving database", lcd);
			retrieveSQL(entries, lcd);	
		} else if (card == 4){
			printTime(lcd);
		} else if (card == 6){
			printLastCoffee(lcd);
		} else if (card == 9){
			changeBacklight(io, backlight, lcd);
		}
	}while (card != -1);
	lcd.clear();
	
	printfl("  Closing DeltaPi", lcd);
	lcd.move(6,2);
	lcd.write("Goodbye!     ",500);
	io.write(23, rpihw::gpio::LOW);
	
	delete backlight;
	return 0;
}
