#ifndef MENU_H
#define MENU_H

#include <list>
#include <string>

#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"

class Menu
{
private:
    std::list<Student> students;
    std::list<Lecturer> lecturers;
    std::list<Administrator> administrators;

    void loadUsers();

    Person* findUser(const std::string& id);

public:
    void showLoginMenu();
    void run();
};

#endif