#include "Lecturer.h"

#include <iostream>

using namespace std;

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
    cout << "3. Close attendance session\n";
    cout << "0. Logout\n";

    // TODO: Menu choice handling will be connected by the Menu/UI layer.
}

void Lecturer::viewEnrolment(Course& course) const
{
    // TODO: Display enrolments only for the lecturer's own course.
    // This will use the final Course and Enrolment implementations.

    (void)course;
}

void Lecturer::openAttendanceSession(const TimeSlot& slot)
{
    // TODO: Connect to Member 2's AttendanceSession implementation.
    // The session must be opened for one of the lecturer's own
    // course time slots.

    (void)slot;
}

void Lecturer::closeAttendanceSession()
{
    // TODO: Connect to Member 2's AttendanceSession implementation.
}