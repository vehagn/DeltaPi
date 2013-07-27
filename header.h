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

/* MySQL Connector/C++ specific headers */
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include <cppconn/stdexcept>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/warning.h>

#define DBHOST "mysql.stud.ntnu.no" //Database host
#define USER "delta_root" //Database user
#define PASSWORD "Delta_xx" //Database password
#define DATABASE "delta_base" //Database directory

/*
TO DO:
update database connection info (encrypted file)
*/

using namespace std;
using namespace sql;

const int maxCredit = 200; //Maximum allowed credit


//Entry
class Entry{
private:

	int cardId;
	string firstName;
	string lastName;

	bool tab;
	int cash;
	long spent;

	string comment;

public:
	Entry();
	~Entry();
	Entry(int, string, string, bool, int, long, string);

	void setInfo(map<const int,Entry> *);

	int getID();
	string getNameFirstLast();
	string getFirstName();
	string getLastName();

	int getCash();
	long getSpent();

	string getComment();

	bool getTab();
	void openTab(bool);

	void printBalance();
	void setBalance(string);
};

//Actions
void scanCard(map<const int,Entry> *, int);
void beerMode(string, map<const int,Entry> *);

void openTab(string, map<const int,Entry> *);

void exportHTML(map<const int,Entry> *);


//Misc
int beerScan(map<const int,Entry> *, int);

int getCard(map<const int,Entry> *);
int checkLogin(time_t *,int*);
bool checkAlnum(string);

char* str2char(string);

void connectToTheWired(LPCTSTR pszURL);
void talkToTheWired(LPCTSTR pszURL);

//SQL
int retrieveSQL(map<const int,Entry> &);
int updateSQL(int, string, int);
