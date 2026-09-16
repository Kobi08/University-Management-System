#include "Administrator.h"
#include <iostream>

using namespace std;

Administrator::Administrator(const string& name, const string& password)
    : Person(name, password)
{
}

void Administrator::showMenu()
{
    cout << "\n====================================\n";
    cout << "       ADMINISTRATOR DASHBOARD      \n";
    cout << "====================================\n";
    cout << "Administrator Name : " << getName() << "\n";
    cout << "Administrator ID   : " << getId() << "\n";
    cout << "1. Manage Users\n";
    cout << "2. Manage Courses\n";
    cout << "3. Generate Enrolment Report\n";
    cout << "4. Logout\n";
    cout << "====================================\n";
}

void Administrator::createuser(const string& name, const string& id, const string& role)
{
    cout << "\nUser creation requires user-management storage integration: "
         << name << " (ID: " << id << ", Role: " << role << ")\n";
}

void Administrator::updateuser(const string& id, const string& newname, const string& newpass)
{
    cout << "\nUser update requires user-management storage integration: ID "
         << id << " (New Name: " << newname << ")\n";
}

bool Administrator::removeuser(const string& id)
{
    cout << "\nUser removal requires user-management storage integration: ID " << id << "\n";
    return false;
}

bool Administrator::createcourse(const string& code, const string& title, int credits, int capacity,
                                  Lecturer& assignedlecturer, const list<string>& prerequisites,
                                  const string& coursetype)
{
    cout << "\nCourse creation requires course-management storage integration: "
         << code << " - " << title << " (" << coursetype << ", Credits: " << credits
         << ", Capacity: " << capacity << ", Assigned Lecturer: "
         << assignedlecturer.getName() << ", Prerequisites: " << prerequisites.size() << ")\n";
    return false;
}

void Administrator::editcourse(const string& code, const string& newcode, const string& newtitle,
                               int newcredits, int newcapacity, Lecturer& newassignedlecturer,
                               const list<string>& newprerequisites, const string& newcoursetype)
{
    cout << "\nCourse editing requires course-management storage integration: "
         << code << " -> " << newcode << " - " << newtitle << " (" << newcoursetype
         << ", Credits: " << newcredits << ", Capacity: " << newcapacity
         << ", Lecturer: " << newassignedlecturer.getName() << ", Prerequisites: "
         << newprerequisites.size() << ")\n";
}

bool Administrator::removecourse(const string& code)
{
    cout << "\nCourse removal requires course-management storage integration: " << code << "\n";
    return false;
}

void Administrator::generateenrolmentreport() const
{
    cout << "\nEnrolment report generation requires Enrolment integration.\n";
}
