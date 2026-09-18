#include "Student.h"
#include "Course.h"
#include "Exceptions.h"
#include "Enrolment.h"

#include <iostream>

using namespace std;

Student::Student(const string& name,
                 const string& password)
    : Person(name, password),
      timetable(nullptr)
{
}

void Student::showMenu()
{
    cout << "\n===== Student Menu (" << getName() << ") =====\n";
    cout << "1. Enroll in a course\n";
    cout << "2. Drop a course\n";
    cout << "3. View my timetable\n";
    cout << "4. Check course completion\n";
    cout << "0. Logout\n";

    // TODO: Menu choice handling will be connected by the Menu/UI layer.
}

void Student::enrollCourse(Course& course)
{
    if (course.isFull())
    {
        throw CourseFullException(
            "Cannot enrol: course is full."
        );
    }

    // TODO: Check prerequisite requirements.
    // Recursive prerequisite validation will be completed
    // when the required student completion history and
    // prerequisite course information are available.

    // TODO: Check timetable clashes using Member 2's final Timetable.

    // TODO: Create and register the Enrolment using the
    // final Enrolment/Repository integration.
}
void Student::dropCourse(Course& course)
{
    // TODO: Complete course-drop logic using the Enrolment class.
    // TODO: Connect timetable removal using Member 2's
    // final Timetable implementation.

    (void)course;
}

bool Student::hasCompleted(const string& courseCode) const
{
    // TODO: Check the student's Enrolment records once
    // the Enrolment implementation is available.

    (void)courseCode;
    return false;
}

bool Student::isEnrolled(const Course& course) const
{
    // TODO: Check the student's Enrolment records once
    // the Enrolment implementation is available.

    (void)course;
    return false;
}

void Student::viewTimetable() const
{
    // TODO: Implement using Member 2's final Timetable
    // implementation once it is available.
}

ostream& operator<<(ostream& os, const Student& student)
{
    os << "Student [Name: " << student.getName()
       << ", ID: " << student.getId() << "]";

    return os;
}