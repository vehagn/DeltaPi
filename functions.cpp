#include "header.h"

void moveAndClearLine(int i, int j, hd44780 &lcd){
	lcd.move(i,j);
	lcd.write("                    ");
	lcd.move(i,j);
}
char getch(){
        struct termios old_tio, new_tio;
        char buf = 0;
        
        tcgetattr(STDIN_FILENO,&old_tio);
        new_tio=old_tio;
        new_tio.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

        if (read(0, &buf, 1) < 0)
                perror ("read()");

        tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
        return (buf);     
	
}
void getLine(char buf[], hd44780 &lcd){
	char c;
	int i = 0;
	lcd.setCursor(hd44780::CURSOR_BLINKING);
	uint8_t startx = lcd.getXCursor();
	uint8_t starty = lcd.getYCursor();	
	uint8_t xpos;
	do{
		xpos = lcd.getXCursor();
		c = getch();
		if ((int)c == 127){
			if (i > 0){
				write(1, "\b \b", 3);
				i--;
			}
			xpos = (xpos <= startx)?(startx):(xpos-1);
			lcd.move(xpos,starty);
			lcd.write(' ');
			lcd.move(xpos,starty);
		}else{
			buf[(i++)%128] = c;
			lcd.write(c);
			write(1, &c, 1);
		}
	}while (c != '\n');
	buf[i%128] = '\0';
	lcd.setCursor(hd44780::NO_CURSOR);
}
void printfl(string str, hd44780 &lcd){
	printf("%s\n", str.c_str());
	lcd.write(str);
}

char* str2char(string s){

	char *c=new char[s.size()+1];
	c[s.size()]=0;
	memcpy(c,s.c_str(),s.size());

	return c;
}

void scanCard(map<const int, Entry> &entries, int &card, hd44780 &lcd){
	string input;
	char buf[128];

	do{
		moveAndClearLine(0,0,lcd);
		printfl("Scan:", lcd);
		getLine(buf, lcd);
		input = buf;
		stringstream checkIfNumber(input);
		if (checkIfNumber >> card){
			if (card == -1){return;}
			if (card <= 10){
				printfl(" command",lcd);	
				return;
			}
			if (entries.find(card) == entries.end()){
				moveAndClearLine(0,3,lcd);
				moveAndClearLine(0,2,lcd);
				moveAndClearLine(0,1,lcd);
				printfl("Card ID not found!",lcd);
			}else{
				return;
			}
		}
		else{
			moveAndClearLine(0,3,lcd);
			moveAndClearLine(0,2,lcd);
			moveAndClearLine(0,1,lcd);
			printfl("Invalid input!",lcd);
		}
	}while (true);
	return;
}
void printInfo(map<const int, Entry> &entries, int &card, hd44780 &lcd){
	char buf[128];
	lcd.clear(); lcd.move(0, 0);
	sprintf(buf, "%s", entries.find(card)->second.getFirstName().c_str());
	printfl(buf, lcd);
	lcd.move(0,1);
	sprintf(buf, "Balance: %ikr", entries.find(card)->second.getCash());
	printfl(buf, lcd);
}
void transaction(map<const int, Entry> &entries, int &card, hd44780 &lcd){
	char buf[128];
	string input;
	int *amount = new int(-1);
	moveAndClearLine(0,2,lcd);
	printfl("Amount:", lcd);
	moveAndClearLine(0,3,lcd);
	printfl("Prefix + to deposit.", lcd);
	lcd.move(8,2);
	getLine(buf, lcd);
	input = buf;

	if (input.substr(0,1) == "+"){
		input.erase(0,1);
		if ((*amount = atoi(input.c_str())) && (*amount <= maxAmount)){
			entries.find(card)->second.depositCash(*amount);
			moveAndClearLine(0,1,lcd);
			moveAndClearLine(0,2,lcd);
			sprintf(buf, "%ikr deposited.", *amount);
			printfl(buf, lcd);
			moveAndClearLine(0,3,lcd);
			sprintf(buf, "New balance: %ikr", entries.find(card)->second.getCash());
			printfl(buf, lcd);
			printf("\n");
		}else if(buf[1] == '0'){
			moveAndClearLine(0,1,lcd);
			printfl("You used 0.", lcd);
			moveAndClearLine(0,2,lcd);
			printfl("It's not very ", lcd);
			moveAndClearLine(0,3,lcd);
			printfl("effective...", lcd);
		}else{
			moveAndClearLine(0,2,lcd);
			printfl("Invalid input!", lcd);
			moveAndClearLine(0,3,lcd);
			sprintf(buf, "Input int <= %i", maxAmount);
			printfl(buf, lcd);
		}
	}else{
		if ((*amount = abs(atoi(input.c_str()))) && (*amount <= maxAmount)){
			if ((entries.find(card)->second.getCash() - *amount) >= -((entries.find(card)->second.getTab()*maxCredit))){
				entries.find(card)->second.withdrawCash(*amount);
				entries.find(card)->second.increaseSpent(*amount);
				moveAndClearLine(0,1,lcd);
				moveAndClearLine(0,2,lcd);
				sprintf(buf, "%i kr withdrawn.", *amount);
				printfl(buf, lcd);
				moveAndClearLine(0,3,lcd);
				sprintf(buf, "New balance: %i kr", entries.find(card)->second.getCash());
				printfl(buf, lcd);
			}else{
				moveAndClearLine(0,3,lcd);
				moveAndClearLine(0,2,lcd);
				printfl("Not enough money!",lcd);
			}
		}else if (buf[0] == '0'){
			moveAndClearLine(0,1,lcd);
			printfl("You used 0.", lcd);
			moveAndClearLine(0,2,lcd);
			printfl("It's not very ", lcd);
			moveAndClearLine(0,3,lcd);
			printfl("effective...", lcd);	
		}else{
			moveAndClearLine(0,2,lcd);
			printfl("Invalid input!", lcd);
			moveAndClearLine(0,3,lcd);
			sprintf(buf, "Input int <= %i", maxAmount);
			printfl(buf, lcd);
		}
	}
	updateSQL(card, "cash", entries.find(card)->second.getCash(), lcd);
	updateSQL(card, "spent", entries.find(card)->second.getSpent(), lcd);
}

void printTime(hd44780 &lcd){
	time_t now;
	struct tm timeinfo;
	char buf [64];
	
	time(&now);
	timeinfo = *localtime(&now);
	strftime(buf,64,"%H:%M:%S",&timeinfo);
	
	lcd.clear();
	lcd.move(6,2);
	printfl(buf, lcd);	
}
void printSummary(map<const int, Entry> &entries, hd44780 &lcd){
	map<const int,Entry>::iterator i;
	int persons = 0;
	long money = 0;
	long spent = 0;
	long credit = 0;
	char buf[128];
	
	lcd.clear();
	printfl("Database summary.\nGathering info...",lcd);
	
	for (i = entries.begin(); i != entries.end(); i++){
		persons++;
		if (i->second.getTab()){
			if (i->second.getCash() >= 0){
				money += i->second.getCash();
			}else{
				credit -= i->second.getCash();
			}		
		}else{
			money += i->second.getCash();
		}
		spent += i->second.getSpent();
	}
	lcd.clear();
	sprintf(buf, "Persons:    %5i", persons);
	printfl(buf,lcd);
	sprintf(buf, "Tot Money:  %5li kr", money);
	lcd.move(0,1);
	printfl(buf,lcd);
	sprintf(buf, "Tot Credit: %5li kr", credit);
	lcd.move(0,2);
	printfl(buf,lcd);
	sprintf(buf, "Tot Spent:  %5li kr", spent);
	lcd.move(0,3);
	printfl(buf,lcd);
	sleep(5);
}
