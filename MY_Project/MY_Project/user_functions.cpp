#include<iostream>
#include <stdlib.h>
#include <iomanip>

#include "user_functions.hpp"
#include "connection.hpp"
//#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
string global_username;



int user::user_login()
{
	cout << "Enter Your UserName" << endl;
	cin >> user_name;
	cout << "Enter Your Password" << endl;
	cin >> user_password;

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

	stmt = con->createStatement();


	stmt->execute("use my_project");



	res = stmt->executeQuery("SELECT * FROM user_info where username = '" + user_name + "' and password = '" + user_password + "';  ");
	if (res->next() == 0) {
		cout << "Please enter corretct credentials";
		return -1;
	}
	else {
		while (res->next()) {

			cout << "first name = " << res->getString(3); // getInt(1) returns the first column
			// ... or column names for accessing results.
			// The latter is recommended.

			

		}
		global_username = user_name;
		return 1;
	}
	delete res;
}

void user::your_profile()
{
	int profile_choice;
	string book_name, book_detail, book_id, book_name_ex, book_detail_ex, book_id_ex,don_del,exc_del;
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

	stmt = con->createStatement();


	stmt->execute("use my_project");
	cout << "Choose any one option: \n\n ";
	cout << "1. Add books for DONATION\n";
	cout << "2. Add books for EXCHANGE\n";
	cout << "3. Remove books from DONATION\n";
	cout << "4. Remove books from EXCHANGE\n";
	cin >> profile_choice;
	switch (profile_choice)
	{
	case 1:
		cout << "Enter book id(it should be a integer value): ";
		cin >> book_id;

		cout << "Enter book name : ";
		cin >> book_name;

		cout << "Enter book details: ";
		cin >> book_detail;

		
		user_name=global_username;

		stmt->execute("insert into donation_books(book_id, book_name, book_detail,username)values ('"+book_id+"', '" + book_name + "','" + book_detail + "','" + user_name + "')"
		);
		break;

	case 2: 
		cout << "Enter book id(it should be a integer value): ";
		cin >> book_id_ex;

		cout << "Enter book name : ";
		cin >> book_name_ex;

		cout << "Enter book details: ";
		cin >> book_detail_ex;

		user_name=global_username;

		stmt->execute("insert into exchange_books(book_id, book_name, book_details,username)values ( "+book_id_ex + ", '" + book_name_ex + "','" + book_detail_ex + "','" + user_name + "')"
		);
		break;

	case 3:
		cout << "Enter the book id that you want to delete (it should be a integer value): ";
		cin >> book_id;



		stmt->execute("delete from donation_books WHERE book_id ="+book_id+"");
		
		cout << "Deletion successful";

		break;


	case 4:
		cout << "Enter the book id that you want to delete (it should be a integer value): ";
		cin >> book_id_ex;



		stmt->execute("delete from exchange_books where book_id like " + book_id_ex + "");

		cout << "Deletion successful";
	
	}
}

void user::Donation_books()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

	stmt = con->createStatement();


	stmt->execute("use my_project");

	cout << "Books available for donation are: \n\n\n\n";
	res=stmt->executeQuery("SELECT book_name,book_detail,username FROM donation_books");
	cout
	<< left
		//<< setw(8)
		//<< "BOOK id"
		//<< left
		<< setw(50)
		<< "BOOK NAME "
		<< left
		<< setw(50)
		<< "BOOK DETAILS"
		<< left
		<< setw(15)
		<< "UPLOADED BY THE USER"
		<< endl<<endl<<endl;
	while (res->next()) {
		
		cout
			//<< left
			//<< setw(8)
			//<< res->getInt(1)
			<< left
			<< setw(50)
			<< res->getString(1)
			<< left
			<< setw(50)
			<< res->getString(2)
			<< left
			<< setw(15)
			<< res->getString(3)
			<< endl;
	}


	delete res;



	
		
	

}

void user::Exchange_books()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

	stmt = con->createStatement();


	stmt->execute("use my_project");

	cout << "Books available for exchange are: \n\n\n\n";
	res = stmt->executeQuery("SELECT book_name,book_details,username FROM exchange_books");
	cout
		//<< left
		//<< setw(8)
		//<< "BOOK id"
		<< left
		<< setw(50)
		<< "BOOK NAME "
		<< left
		<< setw(50)
		<< "BOOK DETAILS"
		<< left
		<< setw(15)
		<< "UPLOADED BY THE USER"
		<< endl << endl << endl;

	while (res->next()) {

		cout
			//<< left
			//<< setw(8)
			//<< res->getInt(1)
			<< left
			<< setw(50)
			<< res->getString(2)
			<< left
			<< setw(50)
			<< res->getString(3)
			<< left
			<< setw(15)
			<< res->getString(4)
			<< endl;
	}
	delete res;
}

void user::choosing_functions()
{
	int users_choice;
	cout << "To choose any option enter the respective key: \n\n";
	cout << " 1. See your Profile \n\n";
	cout << " 2. See BOOKS for DONATION \n\n";
	cout << " 3. See BOOKS for EXCHANGE \n\n";
	cout << " 4. Logout \n\n";
	cin >> users_choice;
	user user_choice_f;
	switch (users_choice)
	{
	case 1:
		user_choice_f.your_profile();
		break;

	case 2:
		user_choice_f.Donation_books();
		break;

	case 3:
		user_choice_f.Exchange_books();
		break;


	case 4:
		break;

	}
}