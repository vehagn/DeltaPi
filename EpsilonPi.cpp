#include "header.h"

int main(int argc, char* argv[]){
	
	gpio io;
	//Office
	io.setup(11, gpio::INPUT);
	io.setup(4, gpio::OUTPUT);
	
	//Coffee
	io.setup(10, gpio::INPUT);
	io.setup(22, gpio::OUTPUT);
	
	bool office = false;
	bool coffee = false;
	time_t coffeeTime = 0;
	
	while (true){
		office = io.read(11);
		coffee = io.read(10);
		
		if office{
			io.write(4, gpio::HIGH);
		}else{
			io.write(4, gpio::LOW);
		}
		
		if coffe{
			time(&coffeTime);
		}
		if difftime(time(NULL),coffeTime) < 1*10{
			io.write(22, gpio::HIGH);
		}else{
			io.write(22, gpio::LOW);
		}		
	}	
	return 0;
}