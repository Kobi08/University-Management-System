#include "Lecturer.h"
#include "Course.h"
#include "TimeSlot.h"
#include "AttendanceSession.h"

#include <iostream>

using namespace std;

Lecturer::Lecturer(const string& name,
                   const string& password)
    : Person(name, password),
      activeSession(nullptr)
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

void Lecturer::openAttendanceSession(const TimeSlot& slot,
                                     int durationminute)
{
    for (Course* course : assignedCourse)
    {
        if (course == nullptr)
        {
            continue;
        }

        if (course->getLecturer() != this)
        {
            continue;
        }

        for (const TimeSlot& courseSlot : course->getTimeSlots())
        {
            if (courseSlot == slot)
            {
                if (activeSession != nullptr)
                {
                    activeSession->close();

                    sessionHistory.push_back(activeSession);

                    activeSession = nullptr;
                }

                activeSession =
                    new AttendanceSession(*course,
                                          slot,
                                          durationminute);

                activeSession->open();

                cout << "Attendance session opened for course "
                     << course->getCode() << "." << endl;

                return;
            }
        }
    }

    cout << "This time slot does not belong to one of your courses."
         << endl;
}

void Lecturer::closeAttendanceSession()
{
    if (activeSession == nullptr)
    {
        cout << "No active attendance session." << endl;
        return;
    }

    activeSession->close();

    sessionHistory.push_back(activeSession);

    activeSession = nullptr;

    cout << "Attendance session closed." << endl;
}

void Lecturer::addCourse(Course& course)
{
    assignedCourse.push_back(&course);
}

AttendanceSession* Lecturer::getActiveSession() const
{
    return activeSession;
}

Lecturer::~Lecturer()
{
    if (activeSession != nullptr)
    {
        activeSession->close();
        delete activeSession;
        activeSession = nullptr;
    }

    for (AttendanceSession* session : sessionHistory)
    {
        delete session;
    }

    sessionHistory.clear();
}