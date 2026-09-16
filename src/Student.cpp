#include "Student.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Student::Student(const string& name, const string& password)
    : Person(name, password), timetable()
{
}

void Student::showMenu()
{
    cout << "\n====================================\n";
    cout << "          STUDENT DASHBOARD         \n";
    cout << "====================================\n";
    cout << "Student Name : " << getName() << "\n";
    cout << "Student ID   : " << getId() << "\n";
    cout << "1. View Timetable\n";
    cout << "2. Enroll Course\n";
    cout << "3. Drop Course\n";
    cout << "4. Logout\n";
    cout << "====================================\n";
}

void Student::enrollcourse(Course& course)
{
    if (timetable.hasClash(course))
    {
        throw invalid_argument("Timetable clash detected for course: " + course.getcode());
    }

    throw logic_error("Course enrolment requires Enrolment integration");
}

void Student::dropcourse(Course& course)
{
    throw logic_error("Course withdrawal requires Enrolment integration: " + course.getcode());
}

bool Student::hascompleted(const string& courseCode) const
{
    throw logic_error("Course completion lookup requires Enrolment integration: " + courseCode);
}

bool Student::isenrolled(const Course& course) const
{
    throw logic_error("Course enrolment lookup requires Enrolment integration: " + course.getcode());
}

void Student::viewtimetable() const
{
    timetable.display();
}

ostream& operator<<(ostream& os, const Student& student)
{
    os << "Student [ID: " << student.getId()
       << ", Name: " << student.getName()
       << "]";
    return os;
}
