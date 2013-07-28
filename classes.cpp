#include "header.h"

Entry::Entry(){
	this->cardId = 0;
	this->firstName = "No";
	this->lastName = "Name";
	
	this->tab = false;
	this->cash = 0;
	this->spent = 0;
	
	this->comment = "";
}
Entry::~Entry(){

}
Entry::Entry(int cardID, string lastName, string firstName, bool tab, int cash, long spent, string comment){
	this->cardId = cardID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->tab = tab;
	this->cash = cash;
	this->comment = comment;
}
int Entry::getID(){
	return this->cardId;
}

string Entry::getNameFirstLast(){
	return this->firstName + " " + this->lastName;
}
string Entry::getFirstName(){
	return this->firstName;
}
string Entry::getLastName(){
	return this->lastName;
}
bool Entry::getTab(){
	return this->tab;
}
int Entry::getCash(){
	return this->cash;
}
long Entry::getSpent(){
	return this->spent;
}
string Entry::getComment(){
	return this->comment;
}
void Entry::depositCash(int amount){
	this->cash += amount;
}
void Entry::withdrawCash(int amount){
	this->cash -= amount;
}
void Entry::increaseSpent(int amount){
	this->spent += amount;
} 

void Entry::setBalance(string operation, hd44780 &lcd){
	int *number = new int(0);

	if (operation.substr(0,1) == "+"){
		operation.erase(0,1);
		if((*number = atoi(operation.c_str())) && (*number < 501)){
			this->cash += atoi(operation.c_str());
		}else{
			printf("Invalid input, input must be an integer less than 501\n");
		}
	}else{
		if((*number = abs(atoi(operation.c_str()))) && (*number < 501)){
			if ((this->cash - *number) >= -(this->tab*maxCredit)){
				this->cash -= *number;
				this->spent += *number;
			}else{
				printf("\n\tNot enough money! \a\a\n");
				printf("Max credit is %i kr for this card.\n", this->tab*maxCredit);
			}
		}else{
			printf("Invalid input, input must be an integer less than 501\n");
		}
	}
}
void Entry::printBalance(){
		printf("%i kr",this->getCash());
}
