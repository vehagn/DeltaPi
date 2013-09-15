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
        new_tio.c_lflag &= (~ICANON);
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
	do{
		c = getch();
		if (c == '\b'){
			i--;
		}else{
			buf[(i++)%128] = c;
			lcd.write(c);
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
				sprintf(buf, "New balance:%i kr", entries.find(card)->second.getCash());
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

/*void beerMode(map<const int,Entry> *entries){
	string input;
	int card = -1;

	do{
		cout << endl << "Scan card: ";
		getline(cin,input);

       // card = beerScan(entries,card);
        if (card > 0){
            //entries->find(card)->second.printLine();
            cout << "Current balance: "; entries->find(card)->second.printBalance();
            cout << "\n\nAmount (use \"+amount\" to deposit): ";
            getline(cin,input);
            entries->find(card)->second.setBalance(input);
            cout << "\nNew balance: ";  entries->find(card)->second.printBalance(); cout << endl;
            updateSQL(card,"cash",entries->find(card)->second.getCash());
            updateSQL(card,"spent",entries->find(card)->second.getSpent());
        }else{
			cout << "Incorrect input, type 'help' for more information" << endl;
		}
	}while (true);
}*/
/*int beerScan(map<const int,Entry> &entries, int card){
	string cmd;
	if (card == 0){		
		while (true) {
			cout << endl << "Input: " << endl;
			getline(cin,cmd);
			stringstream checkIfNumber(cmd);
			cout << endl;
			if (checkIfNumber >> card){
				break;
			}
			cout << "Invalid Card ID, please scan again" << endl;
			return -1;
		}
	}else{
		if (entries->find(card) == entries->end()){
			printf("Card ID not found!\n");
			return -1;
		}else{
			return card;
		}
	}return 0;
}*/

/*void connectToTheWired(LPCTSTR pszURL){
	CInternetSession session(_T("sessionID"));
	CStdioFile* pFile = NULL;
	CHAR szBuff[1024];
	string html;
	string text;
	int start = 0;
	int end = 0;
	int counter = 0;
	//use a URL and print a Web page to the console
	try{
		pFile = session.OpenURL(pszURL);
		while (pFile->Read(szBuff, 1024) > 0)
		{
			//printf_s("%1023s", szBuff);
			html.append(szBuff);
		}
		DeleteUrlCacheEntry(pszURL);
		session.Close();
		delete pFile;

		html.erase(0,html.find("<body>")+830);
		html.erase(remove(html.begin(),html.end(),'\t'),html.end());
		html.erase(remove(html.begin(),html.end(),'\n'),html.end());

		do{
			if (html.find("<br />")!=string::npos){
				html.erase(html.find("<br />"),6);	
			}

		} while (html.find("<br />")!=string::npos);
		//cout << html;
		do{
			html.erase(end,1);
			html.erase(start,1);
			start = html.find(">");
			end = html.find("<");
			if ((end-start) > 1 && html.substr(start+1) != " "){
				if (counter++ >= 10){break;}
				text.append(html.substr(start+1,end-start-1));
				text.append("\n");
			}
		} while (html.find("<")!=string::npos);
		cout << text;
	}catch (CInternetException* pEx){
			//catch errors from WinInet
			TCHAR pszError[64];
			pEx->GetErrorMessage(pszError, 64);
			_tprintf_s(_T("%63s"), pszError);
		}
}*/
