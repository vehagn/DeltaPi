#include "header.h"

int updateSQL(int id, string field, int int_value){
	
	int n;
	enum FIELDS{
		id_num,
		last_name,
		first_name,
		tab,
		cash,
		spent,
		comment};

	try {
		Driver *driver;
		Connection *con;
		PreparedStatement *pstmt;
		map<const int,Entry>::iterator it;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		
		/* Connect to the MySQL test database */
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
	}

	return EXIT_SUCCESS;
}

int retrieveSQL(map<const int,Entry> &entries){

	Entry person;

	try {
		Driver *driver;
		Connection *con;
		//Statement *stmt;
		PreparedStatement *pstmt;
		ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		/* Connect to the MySQL test database */
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
	}
	return EXIT_SUCCESS;
}
