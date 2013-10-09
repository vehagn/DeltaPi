#include "header.h"

void getDatabaseDetails(string *DBHOST, string *USER, string *PASSWORD, string *DATABASE){
	
	*DBHOST = "deltahouse.mysql.domeneshop.no"; //Database host
	/*
	*USER = "deltahouse"; //Database user
	*PASSWORD = "kUJvfr4K"; //Database password
	*DATABASE = "deltahouse"; //Database directory
	*/
	
	FILE *dbFile;
	char buf[128];
	
	dbFile = fopen("database.txt","r");
	if (dbFile == NULL) perror ("Couldn't find database.txt");
	fgets(buf, 128, dbFile);
	
	fgets(buf, 128, dbFile);
	cout << "DBHOST: " << *DBHOST << "! \n";
	*DBHOST = buf;
	DBHOST->erase(DBHOST->end());
	cout << "DBHOST: " << *DBHOST << "! \n";
	
	fgets(buf, 128, dbFile);
	*USER = buf;
	USER->erase(USER->end());
	
	fgets(buf, 128, dbFile);
	*PASSWORD = buf;
	PASSWORD->erase(PASSWORD->end());
	
	fgets(buf, 128, dbFile);
	*DATABASE = buf;
	DATABASE->erase(DATABASE->end());
	
	fclose(dbFile);
}

int retrieveSQL(map<const int,Entry> &entries, hd44780 &lcd){

	Entry person;

	try {
		Driver *driver;
		Connection *con;
		PreparedStatement *pstmt;
		ResultSet *res;

		/* Create a connection */
   		driver = get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);

		pstmt = con->prepareStatement("SELECT * FROM dreg_persons");
		res = pstmt->executeQuery();

		string test;

		while (res->next()){
			Entry person(	res->getInt("id"), 
					res->getString("last_name").c_str(), 
					res->getString("first_name").c_str(), 
					res->getInt("tab"), 
					res->getInt("cash"), 
					res->getInt("spent"), 
					res->getString("comment").c_str());				
			entries[res->getInt("id")] = person;
		}

		delete res;
		delete pstmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "
		<< __LINE__ << endl;
		cout << "# ERR: " << e.what() << endl;
		lcd.clear();
		lcd.write("Error retrieving SQL\ndatabase!\nAre you connected to\nthe internet?",50);
	}
	return EXIT_SUCCESS;
}

int updateSQL(int id, string field, int int_value, hd44780 &lcd){
	
	int n;
	enum FIELDS{
		cash,
		spent};

	try {
		Driver *driver;
		Connection *con;
		PreparedStatement *pstmt;
		map<const int,Entry>::iterator it;

		/* Create a connection */
   		driver = get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);

		if (field == "cash") {n = cash;}
		else if (field == "spent") {n = spent;}

		switch (FIELDS(n)){
		case cash:
			pstmt = con->prepareStatement("UPDATE dreg_persons SET cash = ? WHERE id = ? LIMIT 1");
			pstmt->setInt(1,int_value);
			break;
		case spent:
			pstmt = con->prepareStatement("UPDATE dreg_persons SET spent = ? WHERE id = ? LIMIT 1");
			pstmt->setInt(1,int_value);
			break;
		default:
			printf("SQL identifier not recognized!\n");
			break;
		}

		pstmt->setInt(2,id);
		pstmt->executeUpdate();

		delete pstmt;
		delete con;

	} catch (sql::SQLException &e) {
	cout << "# ERR: SQLException in " << __FILE__;
	cout << "(" << __FUNCTION__ << ") on line "
		<< __LINE__ << endl;
		cout << "# ERR: " << e.what() << endl;
		lcd.clear();
		lcd.write("Error updating SQL\ndatabase!\nAre you connected to\nthe internet?",50);
	}
	return EXIT_SUCCESS;
}