/* Standard C++ headers */
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

//#include <afxinet.h> WINDOWS FILE!!!

/* Rpi-hw headers */
#include <rpi-hw.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/gpio.hpp>
#define hd44780 hd44780base
#include <rpi-hw/display/hd44780.hpp>
#undef hd44780

class hd44780 : hd44780base{
	public:
		uint8_t getxpos(){return m_pos_x;}
		uint8_t getypos(){return m_pos_y;}
};

/* MySQL Connector/C++ specific headers */
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/warning.h>

#define DBHOST "deltahouse.mysql.domeneshop.no" //Database host
#define USER "deltahouse" //Database user
#define PASSWORD "kUJvfr4K" //Database password
#define DATABASE "deltahouse" //Database directory

/*
TO DO:
update database connection info (encrypted file)
*/

using namespace std;
using namespace sql;
using namespace rpihw::iface;
using namespace rpihw::display;
using namespace rpihw::utils;

const int maxCredit = 200; //Maximum allowed credit.
const int maxAmount = 500; //Maximum allowed transfer.


//Entry
class Entry{
private:
	int cardId;
	string firstName;
	string lastName;
	string comment;
	int cash;
	long spent;
	bool tab;
public:
	Entry();
	~Entry();
	Entry(int, string, string, bool, int, long, string);

	void setInfo(map<const int,Entry> *);
	int getID();
	string getNameFirstLast();
	string getFirstName();
	string getLastName();
	string getComment();

	int getCash();
	long getSpent();
	bool getTab();
	
	void depositCash(int);
	void withdrawCash(int);
	void increaseSpent(int);
	void openTab(bool);

	/*void printBalance();
	void setBalance(string);*/
};

//Functions
void moveAndClearLine(int, int, hd44780&);
char getch();
void getLine(char[], hd44780&);
void printfl(string, hd44780&);

char* str2char(string);


void scanCard(map<const int, Entry>&, int&, hd44780&);
void printInfo(map<const int, Entry>&, int&, hd44780&);
void transaction(map<const int, Entry>&, int&, hd44780&);
/*void openTab(string, map<const int,Entry> *);

void beerMode(string, map<const int,Entry> *);
void exportHTML(map<const int,Entry> *);


int beerScan(map<const int,Entry> &, int);
int getCard(map<const int,Entry> *);
int checkLogin(time_t *,int*);
bool checkAlnum(string);*/



/*void connectToTheWired(LPCTSTR pszURL);
void talkToTheWired(LPCTSTR pszURL);*/

//SQL
int retrieveSQL(map<const int,Entry> &, hd44780 &lcd);
int updateSQL(int, string, int, hd44780 &lcd);
