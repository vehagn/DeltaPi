#include "header.h"

int main(int argc, char* argv[]){
	
	rpihw::gpio io;
	//Office
	io.setup(11, rpihw::gpio::INPUT);
	io.setup(4, rpihw::gpio::OUTPUT);
	
	//Coffee
	io.setup(10, rpihw::gpio::INPUT);
	io.setup(22, rpihw::gpio::OUTPUT);
	
	bool office = false;
	bool coffee = false;
	time_t coffeeTime = 0;
	
	while (true){
		office = io.read(11);
		coffee = io.read(10);
		
		if (office){
			io.write(4, rpihw::gpio::HIGH);
		}else{
			io.write(4, rpihw::gpio::LOW);
		}
		
		if (coffee){
			time(&coffeeTime);
		}
		if (difftime(time(NULL),coffeeTime) < 1*10){
			io.write(22, rpihw::gpio::HIGH);
		}else{
			io.write(22, rpihw::gpio::LOW);
		}		
	}	
	return 0;
}