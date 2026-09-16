#include "Lecturer.h"
#include <iostream>

using namespace std;

Lecturer::Lecturer(const string& name, const string& password)
    : Person(name, password), assignedcourse()
{
}

void Lecturer::showMenu()
{
    cout << "\n====================================\n";
    cout << "          LECTURER DASHBOARD        \n";
    cout << "====================================\n";
    cout << "Lecturer Name : " << getName() << "\n";
    cout << "Lecturer ID   : " << getId() << "\n";
    cout << "1. View Enrolment\n";
    cout << "2. Open Attendance Session\n";
    cout << "3. Close Attendance Session\n";
    cout << "4. Logout\n";
    cout << "====================================\n";
}

void Lecturer::viewenrolment(Course& course)
{
    cout << "\nViewing enrolment for Course: " << course.getcode() << "\n";
    cout << "Total enrolled students: " << course.viewenrolment().size() << "\n";
}

void Lecturer::openattendancesession(const TimeSlot& slot)
{
    cout << "\nAttendance session opened for: " << slot << "\n";
}

void Lecturer::closeattendancesession()
{
    cout << "\nAttendance session closed.\n";
}
