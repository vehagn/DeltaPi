#include "header.h"

int main(int argc, char* argv[]){
	
	gpio io;
	io.setup(11, gpio::INPUT);
	bool value = false;
	
	while (true){
		value = io.read(11);
		time::sleep(1);
		
		printf("GPIO 11: %s\n",(value)?("HIGH"):("LOW"));	
	}
	
	return 0;
}