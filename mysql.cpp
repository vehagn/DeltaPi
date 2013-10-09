#include "header.h"

char key = 'a';

string str2hex(const string& input){
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

string hex2str(const string& input){
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw invalid_argument("odd length");

    string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = lower_bound(lut, lut + 16, a);
        if (*p != a) throw invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = lower_bound(lut, lut + 16, b);
        if (*q != b) throw invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

string encrypt(string input){
	string encryptThis = input;
	//[REDACTED]
	return str2hex(encryptThis);
}

string decrypt(string input){

	string tmp;
	tmp = hex2str(input);
	input = tmp;

	string decryptThis = input;
	//[REDACTED]
	return decryptThis;
}

void getDatabaseDetails(string *DBHOST, string *USER, string *PASSWORD, string *DATABASE){
	
	FILE *dbFile;
	char buf[128];
	string crypt;
	
	dbFile = fopen("database.txt","r");
	if (dbFile == NULL) perror ("Couldn't find database.txt");
	fgets(buf, 128, dbFile);
	crypt = buf;
	crypt.pop_back();
	
	fgets(buf, 128, dbFile);
	*DBHOST = buf;
	DBHOST->pop_back();
	
	fgets(buf, 128, dbFile);
	*USER = buf;
	USER->pop_back();
	
	fgets(buf, 128, dbFile);
	*PASSWORD = buf;
	PASSWORD->pop_back();
	
	fgets(buf, 128, dbFile);
	*DATABASE = buf;
	
	fclose(dbFile);
	
	if (crypt == "decrypted"){
		dbFile = fopen("database.txt","w");
		
		strncpy(buf, "encrypted\n", 128);
		fputs(buf, dbFile);
		
		strncpy(buf, encrypt(*DBHOST).c_str(), 128);
		fputs(buf, dbFile); fputc('\n', dbFile);
		
		strncpy(buf, encrypt(*USER).c_str(), 128);
		fputs(buf, dbFile); fputc('\n', dbFile);
		
		strncpy(buf, encrypt(*PASSWORD).c_str(), 128);
		fputs(buf, dbFile); fputc('\n', dbFile);
		
		strncpy(buf, encrypt(*DATABASE).c_str(), 128);
		fputs(buf, dbFile);
		
		fclose(dbFile);
	}else if (crypt == "encrypted"){
		*DBHOST   = decrypt(*DBHOST);
		*USER     = decrypt(*USER);
		*PASSWORD = decrypt(*PASSWORD);
		*DATABASE = decrypt(*DATABASE);
	}else{
		fprintf("ERROR: This is not the database-info you are looking for!");
	}
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