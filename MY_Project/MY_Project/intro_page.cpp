#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "admin_info.hpp"
#include"user_functions.hpp"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//#pragma warning( push )
//#pragma warning( disable : 4789 )
 //unused code that generates compiler warning C4789`
//#pragma warning( pop )

using namespace std;


class intro_page
{
public:
    string first_name, last_name, email_id, username, password, state, city, contact_number;
    string age;

    void signup();
    void login();
   
   
    
};


void intro_page::signup()
{
    
    cout << "******************************************\n";

    cout << "*******************************************\n";

    cout << "***************SIGNUP PAGE****************\n";

    cout << "Enter your first_name: " << endl;
    cin >> first_name;

    cout << "Enter your last_name: " << endl;
    cin >> last_name;

    cout << "Enter your age: " << endl;
    cin >> age;

    cout << "Enter your email_id: " << endl;
    cin >> email_id;

    cout << "Enter your contact_number: " << endl;
    cin >> contact_number;

    cout << "Enter your state: " << endl;
    cin >> state;

    cout << "Enter your city: " << endl;
    cin >> city;

    cout << "Create your username: " << endl;
    cin >> username;

    cout << "Create your password: " << endl;
    cin >> password;

    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt;
    driver = get_driver_instance();
    
    con = driver->connect("tcp://127.0.0.1:3306", "root", "Vidushi@9");
    
    stmt = con->createStatement();

    
    stmt->execute("use my_project");
    
    stmt->execute("insert into user_info(first_name,last_name,age,email_id,contact_number,state,city,username,password) values ('" + first_name + "','" + last_name + "','" + age + "','" + email_id + "','" + contact_number + "','" + state + "','" + city + "','" + username + "','" + password + "')"
        );
    

}
void intro_page::login()
{
    int i = 0;

    do
    {

        cout << "LOGIN PAGE\n";
        cout << "PLEASE CHOOSE ONE OF THE THREE OPTIONS : \n";
        cout << "1. Login as Admin\n";
        cout << "2. Login as User\n";
        cout << "3. Exit\n";
        cin >> i;
        if (i == 1)
        {
            admin adm;
            adm.admin_Login();

            break;
        }

        else if (i == 2)
        {
            user user1;
            int fetch_login_conf;
            fetch_login_conf = user1.user_login();
            if (fetch_login_conf == 1) {
                cout << "\n\n\n\n";
                cout << "         LOGIN SUCCESSFUL!!         \n\n";
                user1.choosing_functions();
                
                break;
            }
            
        }
        else if (i == 3)
        {
            cout << "Thank you for visiting our site!";
            break;
        }
    } while (true);
}




int main(void)
{
    int choice;
    cout << endl;
    cout << "******************************************\n";
    cout << "********* WELCOME TO RENT A BOOK *********\n";
    cout << "    Choose any one option to continue......      " << endl;
    cout << " 1.) SIGNUP " << endl;
    cout << " 2.) LOGIN " << endl;
    cin >> choice;
    intro_page intro;
    if (choice==1)
    {
        
        intro.signup();
        cout << "Your signup was successful!!" << endl;
        intro.login();
    }
    else if (choice ==2)
    {
        intro.login();
    }

   
    cout << endl;

    



    return EXIT_SUCCESS;
}

