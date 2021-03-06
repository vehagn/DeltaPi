#include "header.h"

int main(int argc, char* argv[]){
	
	if(daemon(0,0) == -1)
		err(1, NULL);
	
	rpihw::gpio &io = rpihw::gpio::get();
	
	//Office ports
	io.setup(11, rpihw::INPUT);
	io.setup(4, rpihw::OUTPUT);
	
	//Coffee ports
	io.setup(10, rpihw::INPUT);
	io.setup(22, rpihw::OUTPUT);
	
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
	
	//hd44780 lcd(14, 15, 24, 25, 8, 7);
   	//lcd.init(20, 4);
	//lcd.clear();
	
	//lcd.move(0,1);
	//lcd.write("EpsilonPi ver. 0.7.6");
	
	while (true){
		if (!office){	//There is light.
			time(&officeTime);
		}
		if ((int)difftime(time(NULL),officeTime) >= 10){ //Check to close office every 10s
			if (office_prev != office){
				office_prev = true;
				io.write(4, rpihw::LOW);
				officeFile = fopen("/var/www/pi.deltahouse.no/public_html/office.txt","w");
				if (officeFile == NULL){
					perror ("Couldn't open office.txt");
				}else{
					fprintf(officeFile,"off");
					fclose(officeFile);
				}
				//lcd.move(0,3);
				//lcd.write("   Office closed!   ");
				//lcd.move(5,0);
			}
		}else{
			if (office_prev != office){
				office_prev = false;
				io.write(4, rpihw::HIGH);
				sleep(1);
				officeFile = fopen("/var/www/pi.deltahouse.no/public_html/office.txt","w");
				if (officeFile == NULL){
					perror ("Couldn't open office.txt");
				}else{
					fprintf(officeFile,"on");
					fclose(officeFile);
				}
				//lcd.move(0,3);
				//lcd.write("    Office open!    ");
				//lcd.move(5,0);
			}
		}
		
		if (!coffee){	//Coffee button is pressed.
			time(&coffeeTime);
		}	
		if ((int)difftime(time(NULL),coffeeTime) <= 30*60){ //Coffee light stays on for 30*60 s
			if ((coffee_prev != coffee) && (int)difftime(coffeeTime,coffeePress) >= 30){
				io.write(22, rpihw::HIGH);
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
				//lcd.move(0,3);
				//lcd.write("  Brewed today: %2i", coffeePots);
				//lcd.move(5,0);
			}	
		}else{
			if (coffee_prev != coffee){
				io.write(22, rpihw::LOW);
				coffee_prev = coffee;
			}
		}
		
		office = io.read(11);
		coffee = io.read(10);
		usleep(650);
	}	
	return 0;
}
