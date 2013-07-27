#include "header.h"

map<const int, Entry> entries;
Entry person;

int main(int argc, char* argv[]){
	retrieveSQL(entries);
	entries.erase(0);


	return 0;
}
