#ifndef __people_list__
#define __people_list__

#include <string>
#include <unordered_map>

using namespace std;

class Person
{
public:
    Person(string name, string family_name, string id, 
        string phone_number, string email, /* schedule */);
    ~Person();

private:
    string m_name;
    string m_family_name;
    string m_id;
    string m_phone_number;
    string m_email;
    //schedule
}

/* ----------------------------------- */

class Student : public Person
{
public:
    Student(string name, string family_name, string id, 
        string phone_number, string email, /* schedule */, 
        string grade, string m_teacher_name);
    ~Student();

private:
    string m_name;
    string m_family_name;
    string m_id;
    string m_phone_number;
    string m_email;
    //schedule
    string m_grade;
    string m_teacher_name;
}

/* ----------------------------------- */

class Professional_teacher : public Person
{
public:
    Professional_teacher(string name, string family_name, string id, 
        string phone_number, string email, /* schedule */);
    ~Professional_teacher();
    int AccessPermissions();

private:
    string m_name;
    string m_family_name;
    string m_id;
    string m_phone_number;
    string m_email;
    //schedule
}

/* ----------------------------------- */

class Educator : public Person
{
public:
    Educator(string name, string family_name, string id, 
        string phone_number, string email, /* schedule */);
    ~Educator();
    int AccessPermissions();

private:
    string m_name;
    string m_family_name;
    string m_id;
    string m_phone_number;
    string m_email;
    //schedule
}

/* ----------------------------------- */

class ManageList
{
public:
    ManageList();
    ~ManageList();

private:
    unordered_map<string, Person> m_people;
}




#endif //__people_list__