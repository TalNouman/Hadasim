#ifndef __user_management__
#define __user_management__

#include <fstream>
#include <string>

class userManagement
{
public:
    userManagement(string file_name);
    ~userManagement();
    int Register();
    int Login();

private:
    string m_data_file;
    string m_user_name;
    string m_password;
    ifstream m_input;
    ofstream m_output;
};


#endif //__user_management__