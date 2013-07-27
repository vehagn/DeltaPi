#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){
	retrieveSQL(entries);
	entries.erase(0);
	
	printf("\n %s \n", entries.find(10993472)->second.getNameFirstLast());


	return 0;
}
