#include "Lecturer.h"
#include "Course.h"

#include <iostream>

class Enrolment;

Lecturer::Lecturer(const string& name,
                   const string& password)
    : Person(name, password)
{
}

void Lecturer::showMenu()
{
    cout << "\n===== Lecturer Menu (" << getName() << ") =====\n";
    cout << "1. View enrolments\n";
    cout << "2. Open attendance session\n";
    cout << "0. Logout\n";
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

ostream& operator<<(ostream& os,
                         const Lecturer& lecturer)
{
    os << "Lecturer [Name: "
       << lecturer.getName()
       << ", ID: "
       << lecturer.getId()
       << "]";

    return os;
}