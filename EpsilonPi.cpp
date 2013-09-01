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
	
	bool coffee = false;
	bool coffe_prev = !coffee;
	FILE *coffeeFile
	time_t coffeeTime = 0;
	int coffeePots = 0;
	
	time_t startTime = 0;
	time(&startTime);
	
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
			if (coffee_prev != coffee){
				coffee_prev = coffee;
				if (coffeeTime.tm_yday != startTime.tm_yday){
					coffeePots = 0;
					time(&startTime);
				}
				coffeePots++;
				char buf [64];
				strftime(buf,64,"%d. %B %Y %T",localtime(%coffeeTime));
				coffeeFile = fopen("coffee.txt","w");
				fprintf(coffeeFile,"%i\n%s",coffeePots,buf);
				delete[] buf;
				fclose(coffeeFile);
			}
			
		}else{
			io.write(22, rpihw::gpio::LOW);
			if (coffee_prev != coffee){
				coffee_prev = coffee;
			}
		}
		
		office = io.read(11);
		coffee = io.read(10);		
	}	
	return 0;
}