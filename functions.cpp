#include "header.h"

void moveAndClearLine(int i, int j, hd44780 &lcd){
	lcd.move(i, j);
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
	do{
		c = getch();
		buf[(i++)%128] = c;
		lcd.write(c);
	}while (c != '\n');
	buf[i%128] = '\0';
}

void printfl(string str, hd44780 &lcd){
	printf("%s", str.c_str());
	lcd.write(str);
}


void beerMode(map<const int,Entry> *entries){
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
}

int scanCard(map<const int, Entry> &entries, int &card, hd44780 &lcd){
	string input;
	char buf[128];

	do{
		lcd.move(0,0);
		printfl("Card: ", lcd); lcd.write("               "); lcd.move(5,0);
		lcd.setCursor(hd44780::CURSOR_SOLID | hd44780::CURSOR_BLINKING);
		getLine(buf, lcd);
		input = buf;
		stringstream checkIfNumber(input);
		sprintf(buf,"%s\n" ,input.c_str());
		printfl(buf, lcd);
		if (checkIfNumber >> card){
			if (card == -1){return card;}
			break;
		}
		else{
			moveAndClearLine(0, 1, lcd);
			printfl("Invalid input!\n",lcd);
		}
	}while (true);

	if (entries.find(card) == entries.end()){
		moveAndClearLine(0, 1, lcd);
		printfl("Card ID not found!\n",lcd);
		return -2;
	}
	else{
		moveAndClearLine(0,1, lcd);
		printfl(entries.find(card)->second.getFirstName().c_str(), lcd);
		return card;
	}
}

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

char* str2char(string s){

	char *c=new char[s.size()+1];
	c[s.size()]=0;
	memcpy(c,s.c_str(),s.size());

	return c;
}
