#include "Student.h"
#include "Course.h"
#include "Exceptions.h"
#include "Enrolment.h"

#include <iostream>

using namespace std;

Student::Student(const string& name,
                 const string& password)
    : Person(name, password)
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
    if (isEnrolled(course))
{
    throw Exception(
        "Cannot enrol: student is already enrolled in this course."
    );
}

    // TODO: Check prerequisite requirements.
    // Recursive prerequisite validation will be completed
    // when the required student completion history and
    // prerequisite course information are available.

    if (timetable.hasClash(course))
    {
        throw TimetableClashException(
            "Cannot enrol: timetable clash detected."
        );
    }

    Enrolment* enrolment = new Enrolment(
    *this,
    course,
    "Enrolled",
    "2026-09-19",
    0
);

course.addEnrolment(*enrolment);
timetable.addCourse(course);
}

void Student::dropCourse(Course& course)
{
    for (Enrolment* enrolment : course.viewEnrolment())
    {
        if (enrolment != nullptr &&
            enrolment->getStudent() == this)
        {
            course.removeEnrolment(*enrolment);
            timetable.removeCourse(course);
            return;
        }
    }
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
    for (Enrolment* enrolment : course.viewEnrolment())
    {
        if (enrolment != nullptr &&
            enrolment->getStudent() == this &&
            enrolment->getCourse() == &course)
        {
            return true;
        }
    }

    return false;
}

void Student::viewTimetable() const
{
    timetable.display();
}

ostream& operator<<(ostream& os, const Student& student)
{
    os << "Student [Name: " << student.getName()
       << ", ID: " << student.getId() << "]";

    return os;
}