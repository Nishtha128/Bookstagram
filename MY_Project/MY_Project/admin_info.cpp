#include<iostream>
#include<fstream>
#include "admin_info.hpp"
#include <stdlib.h>
#include <iomanip>

//#include "connection.hpp"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


using namespace std;

void admin::admin_welcome_pg()
{
    cout << "Your login as admin was successful!!" << endl;
    cout << "************************************" << endl << endl;
    cout << "OPTIONS AVAILABLE: \n";
    cout << "1. SHOW USERS\n ";
    cout << "2. SHOW BOOKS\n ";
    cout << "3. Logout\n ";
    cin >> j;
     
    while (true)
    {
        switch (j)
        {
        case 1:
            show_users();
            break;

        case 2:
            showbooks();
            break;

        case 3:
            admin_Login();
            break;


        }
        break;
    }

    if (j != 3) {
        admin_welcome_pg();
    }

}

  void admin::showbooks()
  {
      string book_name, book_detail, book_id, book_name_ex, book_detail_ex, book_id_ex, don_del, exc_del;

      cout << "CHOOSE FROM THE FOLLOWING OPTIONS : \n";
      cout << "1. BOOKS FOR DONATION\n";
      cout << "2. BOOKS FOR EXCHANGE\n";
      cout << "3. DELETE A BOOK FROM DONATION BOOKS\n";
      cout << "4. DELETE A BOOK FROM EXCHANGE BOOKS\n";
      cout << "5. GO BACK TO PREVIOUS PAGE\n";
      cin >> k;

      sql::Driver* driver;
      sql::Connection* con;
      sql::Statement* stmt;
      sql::ResultSet* res;
      sql::PreparedStatement* pstmt;
      driver = get_driver_instance();
      con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");

      stmt = con->createStatement();


      stmt->execute("use my_project");

      switch (k)
      {

      case 1:
          cout << "Books available for donation are: \n\n\n\n";
          res = stmt->executeQuery("SELECT * FROM donation_books");
          cout
              << left
              << setw(8)
              << "BOOK id"
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
          while (res->next())
          {
              cout
                  << left
                  << setw(8)
                  << res->getInt(1)
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

          break;


      case 2:
          cout << "Books available for donation are: \n\n\n\n";
          res = stmt->executeQuery("SELECT * FROM exchange_books");
          cout
              << left
              << setw(8)
              << "BOOK id"
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
          while (res->next())
          {
              cout
                  << left
                  << setw(8)
                  << res->getInt(1)
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

          break;

      case 3:
          cout << "Enter the book id that you want to delete (it should be a integer value): ";
          cin >> book_id;



          stmt->execute("delete from donation_books WHERE book_id =" + book_id + "");

          cout << "Deletion successful";

          break;


      case 4:
          cout << "Enter the book id that you want to delete (it should be a integer value): ";
          cin >> book_id_ex;



          stmt->execute("delete from exchange_books where book_id like " + book_id_ex + "");

          cout << "Deletion successful";
          break;

      
      case 5:
          admin_welcome_pg();
          break;



      }
    
  }

  void admin::show_users()
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
      
      res = stmt->executeQuery("SELECT * FROM user_info");
      
   
      cout
          << left
          << setw(20)
          << "First Name"
          << left
          << setw(20)
          << "Last Name "
          << left
          << setw(2)
          << "Age"
          << left
          << setw(20)
          << "Email id"
          << left
          << setw(11)
          <<"Contact Number"
          << left
          << setw(20)
          <<"State"
          << left
          << setw(20)
          <<"City"
          << left
          << setw(20)
          <<"Username"
          << left
          << setw(20)
          <<"Password"
          << endl << endl << endl;
      while (res->next()) {

          cout
              << left
              << setw(20)
              << res->getString(1)
              << left
              << setw(20)
              << res->getString(2)
              << left
              << setw(2)
              << res->getInt(3)
              << left
              << setw(20)
              << res->getString(4)
              << left
              << setw(11)
              << res->getString(5)
              << left
              << setw(20)
              << res->getString(6)
              << left
              << setw(20)
              << res->getString(7)
              << left
              << setw(20)
              << res->getString(8)
              << left
              << setw(20)
              << res->getString(9)
              << endl;
         
      }
      
      
     delete res;

  }


  void admin::admin_Login()
  {
      cout << "Enter Your UserName as an ADMIN" << endl;
      cin >> admin_username;
      cout << "Enter Your Password" << endl;
      cin >> admin_password;

      ifstream Readadminfile;
      Readadminfile.open("admin_info.txt");
      string usnm, pass;

      Readadminfile >> usnm;
      Readadminfile >> pass;

      if (admin_username == usnm && admin_password == pass)
      {

          admin_welcome_pg();

      }
      else
      {
          cout << "login failed !\n"
              << "Invalid username or password!" << endl;
      }
  }