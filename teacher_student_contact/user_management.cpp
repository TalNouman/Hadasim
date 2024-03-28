
#include "user_management.hpp"

userManagement::userManagement(string file_name) : m_data_file(file_name), 
    m_user_name(""), m_password("") 
{
    int user_choice;
    std::cout << "Please enter your chice: " << '\n' << "1 - Register, 2 - Login" << std::endl;
    std::cin >> user_choice;
    switch (user_choice)
    {
    case(1):
        Register();
        Login();
        break;
    case(2);
        Login();
        break;
    default:
        std::cout << "Enter a valid choice" << std::endl;
        break;
    }
}

/* --------------------------------------- */

userManagement::~userManagement() {}

/* --------------------------------------- */

int userManagement::Register()
{
    m_output.open(m_data_file);

    if(!m_output)
    {
        std::cout << "file open failed" << std::endl;
        return 1;
    }
    
    string name, family_name, phone, teacher_name;
    int id, num_class;

    std::cout << "Enter your name: " << std::endl;
    std::cin >> name;
    std::cout << "Enter your family name: " << std::endl;
    std::cin >> family_name;
    std::cout << "Enter your user name: " << std::endl;
    std::cin >> m_user_name;
    std::cout << "Enter your password: " << std::endl;
    std::cin >> m_password;
    std::cout << "Enter your phone: " << std::endl;
    std::cin >> phone;
    std::cout << "Enter your id: " << std::endl;
    std::cin >> id;
    std::cout << "Enter your num class: " << std::endl;
    std::cin >> num_class;
    std::cout << "Enter your teacher name: " << std::endl;
    std::cin >> teacher_name;

    m_output << name << " " << family_name << " " << Uname << " " << pass << " " << phone
        << " " << id << " " << num_class << " " << teacher_name << std::endl;
    
    m_output.close();

    std::cout << "registration completed successfully!" << std::endl;
    return 0;
}

/* --------------------------------------- */

int userManagement::Login()
{
    m_input(m_data_file);
    if(!m_input)
    {
        std::cout << "file open failed" << std::endl;
        return 1;
    }

    string user_name, password;
    std::cout << "Enter user name: " << std::endl;
    std::cin >> user_name;
    std::cout << "Enter your password: " << std::endl;
    std::cin >> password;

    if(m_input >> m_user_name && m_input >> m_password && 
        m_user_name == user_name && m_password == password)
    {
        std::cout << "Login successful!" << std::endl;
    }
    else
    {
        std::cout << "Login failed" << std::endl;
    }

    m_input.colse();

    return 0;
}

/* --------------------------------------- */