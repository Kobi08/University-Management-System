#include "Lecturer.h"
#include "Course.h"
#include "TimeSlot.h"
#include "AttendanceSession.h"
#include "Menu.h"
#include "Enrolment.h"
#include "AttendanceCapture.h"
#include "RotatingCodeCapture.h"
#include "FileReplayCapture.h"
#include "AttendanceRegister.h"
#include "Exceptions.h"
#include "Student.h"
#include <iterator>
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
    if (application == nullptr)
    {
        cout << "Lecturer is not connected "
                "to the application.\n";
        return;
    }

    int choice = -1;

    do
    {
        try
        {
            cout << "\n===== LECTURER MENU =====\n";
            cout << "Lecturer: "
                 << getName()
                 << " ("
                 << getId()
                 << ")\n\n";

            cout << "1. View enrolments\n";
            cout << "2. Open attendance session\n";
            cout << "3. Close attendance session\n";
            cout << "4. Attendance report\n";
            cout << "5. Correct attendance\n";
            cout << "6. Show correction audit\n";
            cout << "0. Logout\n";

            choice =
                application->number(
                    "\nEnter choice: ",
                    0,
                    6
                );

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

                    for (Course* course :
                         assignedCourse)
                    {
                        if (course != nullptr)
                        {
                            cout << course->getCode()
                                 << " - "
                                 << *course
                                 << '\n';
                        }
                    }

                    string code =
                        application->ask(
                            "Enter course code: "
                        );

                    Course* selected =
                        nullptr;

                    for (Course* course :
                         assignedCourse)
                    {
                        if (course != nullptr &&
                            course->getCode() ==
                                code)
                        {
                            selected =
                                course;
                            break;
                        }
                    }

                    if (selected == nullptr)
                    {
                        throw Exception(
                            "That course is not assigned to you."
                        );
                    }

                    viewEnrolment(
                        *selected
                    );

                    break;
                }

                case 2:
                {
                    if (assignedCourse.empty())
                    {
                        throw Exception(
                            "You have no assigned courses."
                        );
                    }

                    cout << "\n===== YOUR COURSES =====\n";

                    for (Course* course :
                         assignedCourse)
                    {
                        if (course != nullptr)
                        {
                            cout << course->getCode()
                                 << '\n';
                        }
                    }

                    string code =
                        application->ask(
                            "Course code: "
                        );

                    Course* selectedCourse =
                        nullptr;

                    for (Course* course :
                         assignedCourse)
                    {
                        if (course != nullptr &&
                            course->getCode() ==
                                code)
                        {
                            selectedCourse =
                                course;
                            break;
                        }
                    }

                    if (selectedCourse == nullptr)
                    {
                        throw Exception(
                            "That course is not assigned to you."
                        );
                    }

                    const list<TimeSlot> slots =
                        selectedCourse->getTimeSlots();

                    if (slots.empty())
                    {
                        throw Exception(
                            "This course has no time slots."
                        );
                    }

                    cout << "\n===== TIME SLOTS =====\n";

                    int position = 1;

                    for (const TimeSlot& slot :
                         slots)
                    {
                        cout << position
                             << ". "
                             << slot
                             << '\n';

                        ++position;
                    }

                    int slotChoice =
                        application->number(
                            "Select slot: ",
                            1,
                            static_cast<int>(
                                slots.size()
                            )
                        );

                    auto selectedIt =
                        slots.begin();

                    std::advance(
                        selectedIt,
                        slotChoice - 1
                    );

                    const TimeSlot selectedSlot =
                        *selectedIt;

                    int duration =
                        application->number(
                            "Session duration in minutes: ",
                            1,
                            240
                        );

                    cout << "\n1. Rotating session code\n";
                    cout << "2. File replay\n";

                    int captureChoice =
                        application->number(
                            "Capture method: ",
                            1,
                            2
                        );

                    AttendanceCapture* capture =
                        nullptr;

                    if (captureChoice == 1)
                    {
                        capture =
                            new RotatingCodeCapture();
                    }
                    else
                    {
                        string path =
                            application->ask(
                                "Replay file path "
                                "(example data/replay.txt): "
                            );

                        capture =
                            new FileReplayCapture(
                                path
                            );
                    }

                    openAttendanceSession(
                        selectedSlot,
                        duration,
                        capture
                    );

                    break;
                }

                case 3:
                {
                    closeAttendanceSession();
                    break;
                }

                case 4:
                {
                    string code =
                        application->ask(
                            "Course code: "
                        );

                    Course* course =
                        nullptr;

                    for (Course* candidate :
                         assignedCourse)
                    {
                        if (candidate != nullptr &&
                            candidate->getCode() ==
                                code)
                        {
                            course =
                                candidate;
                            break;
                        }
                    }

                    if (course == nullptr)
                    {
                        throw Exception(
                            "That course is not assigned to you."
                        );
                    }

                    cout << "\n===== ATTENDANCE REPORT =====\n";

                    cout << "Course: "
                         << course->getCode()
                         << '\n';

                    cout << "Overall attendance: "
                         << application->attendance
                                .getcoursepercentage(
                                    *course
                                )
                         << "%\n";

                    for (Enrolment* enrolment :
                         course->viewEnrolment())
                    {
                        if (enrolment == nullptr ||
                            enrolment->getStudent() ==
                                nullptr)
                        {
                            continue;
                        }

                        Student* student =
                            enrolment->getStudent();

                        cout << student->getId()
                             << " - "
                             << student->getName()
                             << ": "
                             << application->attendance
                                    .getstudentpercentage(
                                        *student,
                                        *course
                                    )
                             << "%\n";
                    }

                    break;
                }

                case 5:
                {
                    string courseCode =
                        application->ask(
                            "Course code: "
                        );

                    Course* course =
                        nullptr;

                    for (Course* candidate :
                         assignedCourse)
                    {
                        if (candidate != nullptr &&
                            candidate->getCode() ==
                                courseCode)
                        {
                            course =
                                candidate;
                            break;
                        }
                    }

                    if (course == nullptr)
                    {
                        throw Exception(
                            "That course is not assigned to you."
                        );
                    }

                    string studentId =
                        application->ask(
                            "Student ID: "
                        );

                    Student* student =
                        dynamic_cast<Student*>(
                            application->findUser(
                                studentId
                            )
                        );

                    if (student == nullptr)
                    {
                        throw Exception(
                            "Student not found."
                        );
                    }

                    AttendanceSession* session =
                        nullptr;

                    if (activeSession != nullptr &&
                        activeSession->getCourse() ==
                            course)
                    {
                        session =
                            activeSession;
                    }
                    else
                    {
                        for (auto it =
                                 sessionHistory.rbegin();
                             it !=
                                 sessionHistory.rend();
                             ++it)
                        {
                            if (*it != nullptr &&
                                (*it)->getCourse() ==
                                    course)
                            {
                                session =
                                    *it;

                                break;
                            }
                        }
                    }

                    if (session == nullptr)
                    {
                        throw Exception(
                            "No attendance session exists "
                            "for this course."
                        );
                    }

                    cout << "1. Present\n";
                    cout << "2. Late\n";
                    cout << "3. Absent\n";

                    int statusChoice =
                        application->number(
                            "Corrected status: ",
                            1,
                            3
                        );

                    string status;

                    if (statusChoice == 1)
                    {
                        status = "Present";
                    }
                    else if (statusChoice == 2)
                    {
                        status = "Late";
                    }
                    else
                    {
                        status = "Absent";
                    }

                    string reason =
                        application->ask(
                            "Correction reason: "
                        );

                    application->attendance.correct(
                        *student,
                        *session,
                        *this,
                        status,
                        reason
                    );
                    application->save();
                    cout << "Correction recorded.\n";

                    break;
                }

                case 6:
                {
                    application->attendance.showAudit();
                    break;
                }

                case 0:
                {
                    logout();
                    cout << "Logged out.\n";
                    break;
                }
            }
        }
        catch (const Exception& error)
        {
            cout << "Error: "
                 << error.what()
                 << '\n';
        }
        catch (const std::exception& error)
        {
            cout << "Error: "
                 << error.what()
                 << '\n';
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

void Lecturer::openAttendanceSession(
    const TimeSlot& slot,
    int durationminute,
    AttendanceCapture* capture)
{
    Course* selectedCourse =
        nullptr;

    TimeSlot selectedSlot;

    for (Course* course :
         assignedCourse)
    {
        if (course == nullptr ||
            course->getLecturer() != this)
        {
            continue;
        }

        for (const TimeSlot& courseSlot :
             course->getTimeSlots())
        {
            // Exact matching here.
            // operator== is intentionally reserved
            // for timetable-overlap detection.
            const bool exactMatch =
                courseSlot.getDay() ==
                    slot.getDay() &&
                courseSlot.getStartTime() ==
                    slot.getStartTime() &&
                courseSlot.getEndTime() ==
                    slot.getEndTime() &&
                courseSlot.getLocation() ==
                    slot.getLocation();

            if (exactMatch)
            {
                selectedCourse =
                    course;

                selectedSlot =
                    courseSlot;

                break;
            }
        }

        if (selectedCourse != nullptr)
        {
            break;
        }
    }

    if (selectedCourse == nullptr)
    {
        delete capture;

        throw Exception(
            "This time slot does not belong "
            "to one of your courses."
        );
    }

    if (activeSession != nullptr)
    {
        activeSession->close();

        sessionHistory.push_back(
            activeSession
        );

        activeSession = nullptr;
    }

    activeSession =
        new AttendanceSession(
            *selectedCourse,
            selectedSlot,
            durationminute
        );

    activeSession->setcapturemethod(
        capture
    );

    try
    {
        activeSession->open();
    }
    catch (...)
    {
        delete activeSession;
        activeSession = nullptr;
        throw;
    }

    if (application != nullptr)
    {
        application->attendance.registerSession(
            *activeSession
        );
    }

    cout << "Attendance session opened for course "
         << selectedCourse->getCode()
         << ".\n";

    cout << "Capture method: "
         << activeSession->captureName()
         << '\n';

    // File replay immediately processes all
    // events in the selected replay file.
    if (activeSession->captureName() ==
        "FileReplay")
    {
        cout << "\n===== FILE REPLAY =====\n";

        while (true)
        {
            try
            {
                string studentId =
                    activeSession->captureNext();

                if (studentId.empty())
                {
                    break;
                }

                Person* person =
                    application->findUser(
                        studentId
                    );

                Student* student =
                    dynamic_cast<Student*>(
                        person
                    );

                if (student == nullptr)
                {
                    cout << "Rejected "
                         << studentId
                         << ": student not found.\n";

                    continue;
                }

                application->attendance.markpresent(
                    *student,
                    *activeSession
                );

                cout << "Marked present: "
                     << studentId
                     << '\n';
            }
            catch (const CorruptDataException& error)
            {
                // The bad line was consumed by
                // FileReplayCapture, so processing
                // can safely continue.
                cout << "Malformed replay event rejected: "
                     << error.what()
                     << '\n';
            }
            catch (const SessionClosedException& error)
            {
                cout << "Replay stopped: "
                     << error.what()
                     << '\n';

                break;
            }
            catch (const Exception& error)
            {
                cout << "Replay event rejected: "
                     << error.what()
                     << '\n';
            }
        }

        cout << "===== END FILE REPLAY =====\n";
    }
    if (application != nullptr)
{
    application->save();
}
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

   if (application != nullptr)
{
    application->save();
}

cout << "Attendance session closed."
     << endl;
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