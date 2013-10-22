#include "header.h"

int main(int argc, char* argv[]){
	
	if(daemon(0,0) == -1)
		err(1, NULL);
	
	rpihw::gpio io;
	
	//Office ports
	io.setup(11, rpihw::gpio::INPUT);
	io.setup(4, rpihw::gpio::OUTPUT);
	
	//Coffee ports
	io.setup(10, rpihw::gpio::INPUT);
	io.setup(22, rpihw::gpio::OUTPUT);
	
	bool office = io.read(11);
	bool office_prev = !office;
	FILE *officeFile;
	time_t officeTime = 0;
	
	bool coffee = true;
	bool coffee_prev = !coffee;
	FILE *coffeeFile;
	FILE *coffeeLog;
	time_t coffeeTime = 0;
	time_t coffeePress = 0;
	int coffeePots = 0;
	
	time_t startTime = 0;
	time(&startTime);
	int startDay = localtime(&startTime)->tm_yday;
	struct tm * timeinfo;
	
	hd44780 lcd(14, 15, 24, 25, 8, 7);
   	lcd.init(20, 4);
	lcd.clear();
	
	lcd.move(0,1);
	lcd.write("EpsilonPi ver. 0.7.5");
	
	while (true){
		if (!office){	//There is light.
			time(&officeTime);
		}
		if ((int)difftime(time(NULL),officeTime) >= 30*60){
			if (office_prev != office){
				office_prev = true;
				io.write(4, rpihw::gpio::LOW);
				officeFile = fopen("/var/www/pi.deltahouse.no/public_html/office.txt","w");
				if (officeFile == NULL){
					perror ("Couldn't open office.txt");
				}else{
					fprintf(officeFile,"1024");
					fclose(officeFile);
				}
				lcd.move(0,3);
				lcd.write("   Office closed!   ");
				lcd.move(5,0);
			}
		}else{
			if (office_prev != office){
				office_prev = false;
				io.write(4, rpihw::gpio::HIGH);
				sleep(1);
				officeFile = fopen("/var/www/pi.deltahouse.no/public_html/office.txt","w");
				if (officeFile == NULL){
					perror ("Couldn't open office.txt");
				}else{
					fprintf(officeFile,"0");
					fclose(officeFile);
				}
				lcd.move(0,3);
				lcd.write("    Office open!    ");
				lcd.move(5,0);
			}
		}
		
		if (!coffee){	//Coffee button is pressed.
			time(&coffeeTime);
		}	
		if ((int)difftime(time(NULL),coffeeTime) <= 60*60){
			if ((coffee_prev != coffee) && (int)difftime(coffeeTime,coffeePress) >= 30){
				io.write(22, rpihw::gpio::HIGH);
				char buf [64];
				coffee_prev = coffee;
				time(&coffeePress);
				timeinfo = localtime(&coffeePress);
				if (timeinfo->tm_yday != startDay){
					coffeePots = 0;
					time(&startTime);
					startDay = localtime(&startTime)->tm_yday;
				}
				coffeePots++;
				strftime(buf,64,"%d. %B %Y %T",timeinfo);
				
				coffeeFile = fopen("/var/www/pi.deltahouse.no/public_html/coffee.txt","w");
				if (coffeeFile == NULL){
					perror ("Couldn't open coffee.txt");
				}else{
					fprintf(coffeeFile,"%i\n%s",coffeePots,buf);
					fclose(coffeeFile);
				}
				
				coffeeLog = fopen("/var/www/pi.deltahouse.no/public_html/coffee_log.txt","a+");
				if (coffeeLog == NULL){
					perror ("Couldn't open coffee_log.txt");
				}else{
					fprintf(coffeeLog,"%i:%s\n",coffeePots,buf);
					fclose(coffeeLog);
				}
				lcd.move(0,3);
				lcd.write("  Brewed today: %2i", coffeePots);
				lcd.move(5,0);
			}	
		}else{
			if (coffee_prev != coffee){
				io.write(22, rpihw::gpio::LOW);
				coffee_prev = coffee;
			}
		}
		
		office = io.read(11);
		coffee = io.read(10);
		sleep(1);
	}	
	return 0;
}
