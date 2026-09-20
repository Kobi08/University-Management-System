#include "Lecturer.h"
#include "Course.h"
#include <limits>
#include <stdexcept>

#include <iostream>

class Enrolment;

Lecturer::Lecturer(const string& name,
                   const string& password)
    : Person(name, password)
{
}

Lecturer::Lecturer(const string& name,
                   const string& password,
                   const string& id)
    : Person(name, password, id)
{
}


void Lecturer::showMenu()
{
    int choice=-1;

    do
    {
        cout << "\n===== Lecturer Menu (" << getName() << ") =====\n";
        cout << "1. View Enrolments\n";
        cout << "2. Open Attendance Session\n";
        cout << "0. Logout\n";

        cout << "\nEnter choice: ";

if (!(cin >> choice))
{
    if (cin.eof())
    {
        return;
    }

    if (cin.bad())
    {
        throw std::runtime_error("Console input failed.");
    }

    cin.clear();

    cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    cout << "Please enter a menu number.\n";
    continue;
}

        switch (choice)
        {
        case 1:
            cout << "View Enrolments integration coming next.\n";
            break;

        case 2:
            cout << "Attendance session integration coming next.\n";
            break;

        case 0:
            logout();
            cout << "Logged out.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

void Lecturer::viewEnrolment(Course& course) const
{
    cout << "\nEnrolments for course:\n";
    cout << course << endl;

    for (Enrolment* enrolment : course.viewenrolment())
    {
        if (enrolment != nullptr)
        {
            //cout<<*enrolment<<endl;
            cout<<"Enrolment details will be available after Enrolment is implemented";
        }
    }
}

void Lecturer::openAttendance(Course& course)
{
    cout << "\nOpening attendance for:\n";
    cout << course << endl;

    // AttendanceSession will be connected later.
}

void Lecturer::assignCourse(Course& course)
{
    assignedCourse.push_back(&course);
}

std::list<Course*> Lecturer::getAssignedCourses() const
{
    return assignedCourse;
}

ostream& operator<<(ostream& os, const Lecturer& lecturer)
{
    os << lecturer.getId() << "|"
       << lecturer.getName() << "|"
       << lecturer.getPassword();

    return os;
}