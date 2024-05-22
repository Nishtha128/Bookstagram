#include<iostream>
#include <stdlib.h>

//#include "user_functios.hpp"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


using namespace std;

void connection()
{
	int profile_choice;
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

	stmt = con->createStatement();


	stmt->execute("use my_project");
	
}