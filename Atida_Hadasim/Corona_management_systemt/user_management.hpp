#ifndef __user_management__
#define __user_management__

#include <iostream>
#include <fstream>
#include <cstring>
#include <sqlite3.h>

class userManagement 
{
public:
    userManagement();
    ~userManagement();
    void CreateDB();
    int AddUser();
    int deleteUser();
    int updateUsersDetails();
    int ReadUsersDetails();
    bool isDigit(const std::string& str);
    int ExecuteQuery(const char* sql, std::string newValue, std::string id, int choice);
    
private:
    sqlite3 *m_db;
};

#endif //__user_management__
