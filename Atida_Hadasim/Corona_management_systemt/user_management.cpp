#include <vector>
//#include <cstdio> 

#include "user_management.hpp"

userManagement::userManagement()
{
    CreateDB();
}

/* --------------------------------------- */

userManagement::~userManagement() 
{
    sqlite3_close(m_db);
} 

/* --------------------------------------- */

void userManagement::CreateDB()
{
    // open db
    if(sqlite3_open("users_data.db", &m_db) != 0)
    {
        std::cout << "Open SQL failed" << sqlite3_errmsg(m_db) << std::endl;
        return;
    }

    // Check if the table already exists
    const char* check_sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='USERS';";
    sqlite3_stmt* check_statement;
    if (sqlite3_prepare_v2(m_db, check_sql, -1, &check_statement, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_close(m_db);
        return;
    }
    int result = sqlite3_step(check_statement);
    sqlite3_finalize(check_statement);

    // Table already exists, no need to create it
    if(result == SQLITE_ROW) 
    {
        return;
    }

    // create a table 
    const char* sql = "CREATE TABLE USERS(" \
                  "NAME           TEXT    NOT NULL," \
                  "FAMILY_NAME    TEXT    NOT NULL," \
                  "ID             CHAR(50)  NOT NULL," \
                  "ADDRESS        CHAR(50)," \
                  "BIRTH_DATE     CHAR(50)    NOT NULL," \
                  "PHONE          CHAR(50)    NOT NULL," \
                  "MOBILE         CHAR(50) NOT NULL," \
                  "VACC_DATE1     CHAR(50)," \
                  "VACC_DATE2     CHAR(50)," \
                  "VACC_DATE3     CHAR(50)," \
                  "VACC_DATE4     CHAR(50)," \
                  "VACC_MANU1     CHAR(50)," \
                  "VACC_MANU2     CHAR(50)," \
                  "VACC_MANU3     CHAR(50)," \
                  "VACC_MANU4     CHAR(50)," \
                  "ILLNESS_DATE   CHAR(50)," \
                  "RECOVERY_DATE  CHAR(50));";

    char* error_msg = 0;

    if(sqlite3_exec(m_db, sql, 0, 0, &error_msg) != SQLITE_OK) 
    {
        std::cerr << "SQL error: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
}

/* --------------------------------------- */

int userManagement::AddUser()  
{
    // ensure data integrity - in case of crush changes didnt save
    if(sqlite3_exec(m_db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Transaction begin failed: " << sqlite3_errmsg(m_db) << std::endl;
        return 1;
    }

    //prepare the query for users's data
    const char *sql = "INSERT INTO USERS (NAME,FAMILY_NAME,ID,ADDRESS,BIRTH_DATE,PHONE,MOBILE," \
                  "VACC_DATE1,VACC_DATE2,VACC_DATE3,VACC_DATE4,VACC_MANU1,VACC_MANU2," \
                  "VACC_MANU3,VACC_MANU4,ILLNESS_DATE,RECOVERY_DATE) " \
                  "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

    sqlite3_stmt *statement;

    if(sqlite3_prepare_v2(m_db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::cout << "Prepare statement failed " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(statement);

        //ROLLBACK - in case of crush cancel the changes
        sqlite3_exec(m_db, "ROLLBACK", nullptr, nullptr, nullptr); 
        return 1;
    }
    
    // get the user's data from the user
    std::string name(""), family_name(""); 
    std::string phone(""), mobile(""), id(""), address(""), birth_date("");
    std::string vacc_date1(""), vacc_date2(""), vacc_date3(""), vacc_date4("");
    std::string vacc_manu1(""), vacc_manu2(""), vacc_manu3(""), vacc_manu4("");
    std::string ilness_date(""), recovery_date("");

    std::cout << "Enter your name: " << std::endl;
    std::cin >> name;
    std::cout << "Enter your family name: " << std::endl;
    std::cin >> family_name;
    std::cout << "Enter your id: " << std::endl;
    std::cin >> id;
    while(id.length() != 9 || !isDigit(id))
    {
        std::cout << "id incorrect. please enter a valid number" << std::endl;
        std::cin >> id;
    }
    std::cout << "Enter your address (apartment's num/street/city): " << std::endl;
    std::cin >> address;
    std::cout << "Enter your birth date (day/month/year): " << std::endl;
    std::cin >> birth_date;
    std::cout << "Enter your home phone: " << std::endl;
    std::cin >> phone;
    while(phone.length() < 9 || !isDigit(phone))
    {
        std::cout << "phone incorrect. please enter a valid number" << std::endl;
        std::cin >> phone;
    }
    std::cout << "Enter your mobile phone: " << std::endl;
    std::cin >> mobile;
    while(mobile.length() != 10 || !isDigit(mobile))
    {
        std::cout << "phone incorrect. please enter a valid number" << std::endl;
        std::cin >> mobile;
    }
    std::cout << "Enter your first vaccination date (day/month/year): " << std::endl;
    std::cin >> vacc_date1;
    std::cout << "Enter your second vaccination date (day/month/year): " << std::endl;
    std::cin >> vacc_date2;
    std::cout << "Enter your third vaccination date (day/month/year): " << std::endl;
    std::cin >> vacc_date3;
    std::cout << "Enter your four vaccination date (day/month/year): " << std::endl;
    std::cin >> vacc_date4;
    std::cout << "Enter your first vaccination manufactor: " << std::endl;
    std::cin >> vacc_manu1;
    std::cout << "Enter your second vaccination manufactor: " << std::endl;
    std::cin >> vacc_manu2;
    std::cout << "Enter your third vaccination manufactor: " << std::endl;
    std::cin >> vacc_manu3;
    std::cout << "Enter your four vaccination manufactor: " << std::endl;
    std::cin >> vacc_manu4;
    std::cout << "Enter your ilness_date(day/month/year): " << std::endl;
    std::cin >> ilness_date;
    std::cout << "Enter your recovery date(day/month/year): " << std::endl;
    std::cin >> recovery_date;

    // bind the input from user to the db
    sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, family_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, id.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 5, birth_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 7, mobile.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 8, vacc_date1.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 9, vacc_date2.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 10, vacc_date3.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 11, vacc_date4.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 12, vacc_manu1.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 13, vacc_manu2.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 14, vacc_manu3.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 15, vacc_manu4.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 16, ilness_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 17, recovery_date.c_str(), -1, SQLITE_STATIC);

    //execute the query
    if(sqlite3_step(statement) != SQLITE_DONE)
    {
        std::cout << "execute statement failed " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(statement);
        sqlite3_exec(m_db, "ROLLBACK", nullptr, nullptr, nullptr); 
        return 1;
    }

    sqlite3_finalize(statement);

    //save the changes in db
    if(sqlite3_exec(m_db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Transaction commit failed: " << sqlite3_errmsg(m_db) << std::endl;
        return 1;
    }

    std::cout << "Add user completed successfully!" << std::endl;
    return 0;
}

/* --------------------------------------- */

int userManagement::deleteUser()
{
    const char* sql = "DELETE FROM USERS WHERE ID = ?;";
    std::string id;
    std::cout << "Enter the id of the user you want to delete" << std::endl;
    std::cin >> id;

    if(ExecuteQuery(sql, id, "", 1) != 0)
    {
        std::cout << "Delete user failed " << sqlite3_errmsg(m_db) << std::endl;
        return 1;
    }

    std::cout << "Delete user completed successfully!" << std::endl;
    return 0;
}

/* --------------------------------------- */

int userManagement::updateUsersDetails()
{
    //check what to change
    int choice;
    std::string id;
    std::cout << "Enter the id of the user you want to update" << std::endl;
    std::cin >> id;
    std::cout << "Please enter your changes choice:" << '\n' << "1(name) 2(family name)" << 
        "3(id) 4(address) 5(birth_date) 6(home phone) 7(mobile)" << std::endl;
    std::cin >> choice;

    // prepare query for each case
    const char *sql = nullptr;
    switch (choice)
    {
    case 1:
        sql = "UPDATE USERS SET NAME = ? WHERE ID = ?;";
        break;
    case 2:
        sql = "UPDATE USERS SET FAMILY_NAME = ? WHERE ID = ?;";
        break;
    case 3:
        sql = "UPDATE USERS SET ID = ? WHERE ID = ?;";
        break;
    case 4:
        sql = "UPDATE USERS SET ADDRESS = ? WHERE ID = ?;";
        break;
    case 5:
        sql = "UPDATE USERS SET BIRTH_DATE = ? WHERE ID = ?;";
        break;
    case 6:
        sql = "UPDATE USERS SET PHONE = ? WHERE ID = ?;";
        break;
    case 7:
        sql = "UPDATE USERS SET MOBILE = ? WHERE ID = ?;";
        break;
    default:
        break;
    }

    std::string changed;
    std::cout << "Write the value you want to add: " << std::endl;
    std::cin >> changed;

    if(ExecuteQuery(sql, changed, id, choice) != 0)
    {
        std::cout << "Update user's details failed " << sqlite3_errmsg(m_db) << std::endl;
        return 1;
    }

    std::cout << "Update user's details completed successfully!" << std::endl;
    return 0;
}

/* --------------------------------------- */

int userManagement::ReadUsersDetails()
{
    const char* sql = "SELECT * FROM USERS WHERE ID = ?;";
    std::string id;
    std::cout << "Enter the id of the user you want to read about" << std::endl;
    std::cin >> id;

    // Prepare the SQL statement
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(m_db, sql, -1, &statement, nullptr) != SQLITE_OK) {
        std::cout << "Prepare statement failed " << sqlite3_errmsg(m_db) << std::endl;
        return 1;
    }

    // Bind the user ID to the prepared statement
    sqlite3_bind_text(statement, 1, id.c_str(), -1, SQLITE_STATIC);

    // Execute the statement and print tha data
    if(sqlite3_step(statement) == SQLITE_ROW) 
    {
        std::cout << '\n' << sqlite3_column_text(statement, 0) << " " <<
            sqlite3_column_text(statement, 1) << " " <<
            sqlite3_column_text(statement, 2) << " " <<
            sqlite3_column_text(statement, 3) << " " <<
            sqlite3_column_text(statement, 4) << " " <<
            sqlite3_column_text(statement, 5) << " " <<
            sqlite3_column_text(statement, 6) << '\n' << std::endl;
        
        // Finalize the statement and close the database
        sqlite3_finalize(statement);
        std::cout << "Read user's details completed successfully!" << std::endl;
        return 0;
    }

    std::cout << "User doesnt exist" << std::endl;
    return 1;
}

/* --------------------------------------- */

bool userManagement::isDigit(const std::string& str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

/* --------------------------------------- */

int userManagement::ExecuteQuery(const char* sql, std::string newValue, std::string id, int choice)
{
    sqlite3_stmt *statement;
    if(sqlite3_prepare_v2(m_db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::cout << "Prepare statement failed " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(statement);
        return 1;
    }

    sqlite3_bind_text(statement, 1, newValue.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, id.c_str(), -1, SQLITE_STATIC);

    if(sqlite3_step(statement) != SQLITE_DONE)
    {
        std::cout << "Execute statement failed " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(statement);
        return 1;
    }

    sqlite3_finalize(statement);

    return 0;
}

/* --------------------------------------- */