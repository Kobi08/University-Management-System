#include "Lecturer.h"
#include "Course.h"
#include "TimeSlot.h"
#include "AttendanceSession.h"
#include "Menu.h"
#include "Enrolment.h"

#include <iostream>
#include <limits>

using namespace std;

Lecturer::Lecturer(const string& name,
                   const string& password)
    : Person(name, password),
      activeSession(nullptr)
{
}

Lecturer::Lecturer(const string& name,
                   const string& password,
                   const string& id)
    : Person(name, password, id),
      activeSession(nullptr)
{
}

void Lecturer::showMenu()
{
    int choice = -1;

    do
    {
        cout << "\n===== LECTURER MENU =====\n";
        cout << "Lecturer: " << getName()
             << " (" << getId() << ")\n\n";

        cout << "1. View enrolments\n";
        cout << "2. Open attendance session\n";
        cout << "3. Close attendance session\n";
        cout << "0. Logout\n";

        cout << "\nEnter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Please enter a valid number.\n";
            continue;
        }

        switch (choice)
        {
case 1:
{
    if (assignedCourse.empty())
    {
        cout << "You have no assigned courses.\n";
        break;
    }

    cout << "\n===== YOUR COURSES =====\n";

    int index = 1;

    for (Course* course : assignedCourse)
    {
        if (course != nullptr)
        {
            cout << index
                 << ". "
                 << course->getCode()
                 << '\n';

            ++index;
        }
    }

    cout << "Enter course code: ";

    string code;
    cin >> code;

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    bool found = false;

    for (Course* course : assignedCourse)
    {
        if (course != nullptr &&
            course->getCode() == code)
        {
            viewEnrolment(*course);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "That course is not assigned to you.\n";
    }

    break;
}

            case 2:
                cout << "Open-attendance integration coming next.\n";
                break;

            case 3:
                closeAttendanceSession();
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
    // Lecturer may only view enrolments
    // for a course assigned to them.
    if (course.getLecturer() != this)
    {
        cout << "You are not assigned to this course.\n";
        return;
    }

    list<Enrolment*> enrolments = course.viewEnrolment();

    cout << "\n===== ENROLMENTS FOR "
         << course.getCode()
         << " =====\n";

    if (enrolments.empty())
    {
        cout << "No students are enrolled in this course.\n";
        return;
    }

    for (Enrolment* enrolment : enrolments)
    {
        if (enrolment != nullptr)
        {
            cout << *enrolment << '\n';
        }
    }
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