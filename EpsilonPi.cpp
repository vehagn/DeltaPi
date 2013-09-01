#include "header.h"

int main(int argc, char* argv[]){
	rpihw::gpio io;
	
	//Office ports
	io.setup(11, rpihw::gpio::INPUT);
	io.setup(4, rpihw::gpio::OUTPUT);
	
	//Coffee ports
	io.setup(10, rpihw::gpio::INPUT);
	io.setup(22, rpihw::gpio::OUTPUT);
	
	bool office = false;
	bool office_prev = !office;
	FILE *officeFile;
	
	bool coffee = true;
	bool coffee_prev = !coffee;
	FILE *coffeeFile;
	time_t coffeeTime = 0;
	time_t coffeePress = 0;
	time(&coffeePress);
	int coffeePots = 0;
	
	time_t startTime = 0;
	time(&startTime);
	struct tm * timeinfo1;
	struct tm * timeinfo2;
	char buf [64];
	
	while (true){
		if (office){
			io.write(4, rpihw::gpio::HIGH);
			if (office_prev != office){
				office_prev = office;
				officeFile = fopen("office.txt","w");
				fprintf(officeFile,"1");
				fclose(officeFile);
			}
		}else{
			io.write(4, rpihw::gpio::LOW);
			if (office_prev != office){
				office_prev = office;
				officeFile = fopen("office.txt","w");
				fprintf(officeFile,"0");
				fclose(officeFile);
			}
		}
		
		if (!coffee){
			time(&coffeeTime);
		}	
		if (difftime(time(NULL),coffeeTime) <= 1*10){
			io.write(22, rpihw::gpio::HIGH);
			printf("Difftime: %i",difftime(coffeeTime,coffeePress));
			if ((coffee_prev != coffee) && (difftime(coffeeTime,coffeePress) > 2)){
				time(&coffeePress);
				coffee_prev = coffee;
				timeinfo1 = localtime(&coffeeTime);
				timeinfo2 = localtime(&startTime);
				if (timeinfo1->tm_yday != timeinfo2->tm_yday){
					coffeePots = 0;
					time(&startTime);
				}
				printf("%i COFFEE PRESS!\n",coffeePots);
				coffeePots++;
				strftime(buf,64,"%d. %B %Y %T",timeinfo1);
				coffeeFile = fopen("coffee.txt","w");
				fprintf(coffeeFile,"%i\n%s",coffeePots,buf);
				fclose(coffeeFile);
			}	
		}else{
			io.write(22, rpihw::gpio::LOW);
			if (coffee_prev != coffee){
				coffee_prev = coffee;
				//time(&coffeePress);
				//timeinfo1 = localtime(&coffeePress);
				//strftime(buf,64,"%d. %B %Y %T",timeinfo1);
				//printf("PRESS TIME: %s \n",buf);
			}
		}
		
		office = io.read(11);
		coffee = io.read(10);		
	}	
	return 0;
}