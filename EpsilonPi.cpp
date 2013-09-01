#include "header.h"

int main(int argc, char* argv[]){
	
	gpio io;
	io.setup(11, gpio::INPUT);
	io.setup(4, gpio::OUTPUT);
	bool value = false;
	
	while (true){
		//value = io.read(11);
		io.write(4, gpio::HIGH);
		time::sleep(1);
		io.write(4, gpio::LOW);
		time::sleep(1);
		printf("GPIO 11: %s\n",(value)?("HIGH"):("LOW"));	
	}
	
	return 0;
}