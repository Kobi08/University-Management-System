#include "Student.h"
#include "Course.h"
#include "Exceptions.h"
#include "Enrolment.h"
#include "Menu.h"
#include <functional>
#include <set>
#include <limits>

#include <ctime>
#include <iomanip>
#include <sstream>
#include <utility>

#include <iostream>

using namespace std;

Student::Student(const string& name,
                 const string& password)
    : Person(name, password)
{
}

Student::Student(const string& name,
                 const string& password,
                 const string& id)
    : Person(name, password, id)
{
}

Student::~Student() = default;

void Student::showMenu()
{
    int choice = -1;

    do
    {
        cout << "\n===== STUDENT MENU =====\n";
        cout << "Student: " << getName()
             << " (" << getId() << ")\n\n";

        cout << "1. View timetable\n";
        cout << "2. Enrol in course\n";
        cout << "3. Drop course\n";
        cout << "4. Check course completion\n";
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

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        try
        {
            switch (choice)
            {
                case 1:
                {
                    viewTimetable();
                    break;
                }

                case 2:
                {
                    if (application == nullptr)
                    {
                        throw Exception(
                            "Student is not connected to the application."
                        );
                    }

                    string code;

                    cout << "Enter course code to enrol: ";
                    getline(cin, code);

                    Course* course =
                        application->findCourse(code);

                    if (course == nullptr)
                    {
                        cout << "Course not found.\n";
                        break;
                    }

                    enrollCourse(*course);

                        application->save();

                        cout << "Successfully enrolled in "
                            << course->getCode()
                            << ".\n";

                    break;
                }

                case 3:
                {
                    if (application == nullptr)
                    {
                        throw Exception(
                            "Student is not connected to the application."
                        );
                    }

                    string code;

                    cout << "Enter course code to drop: ";
                    getline(cin, code);

                    Course* course =
                        application->findCourse(code);

                    if (course == nullptr)
                    {
                        cout << "Course not found.\n";
                        break;
                    }

                    dropCourse(*course);
                       application->save();
                    cout << "Successfully dropped "
                         << course->getCode()
                         << ".\n";

                    break;
                }

                case 4:
                {
                    string code;

                    cout << "Enter course code: ";
                    getline(cin, code);

                    if (hasCompleted(code))
                    {
                        cout << code
                             << " has been completed.\n";
                    }
                    else
                    {
                        cout << code
                             << " has not been completed.\n";
                    }

                    break;
                }

                case 0:
                {
                    logout();
                    cout << "Logged out.\n";
                    break;
                }

                default:
                {
                    cout << "Invalid choice.\n";
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
void Student::enrollCourse(Course& course)
{
    if (isEnrolled(course))
    {
        throw Exception(
            "Cannot enrol: student is already enrolled in this course."
        );
    }

    if (course.isFull())
    {
        throw CourseFullException(
            "Cannot enrol: course is full."
        );
    }

       std::set<std::string> checking;
    std::set<std::string> checked;

    std::function<void(const Course&)> checkPrerequisites;

    checkPrerequisites = [&](const Course& currentCourse)
    {
        const std::string currentCode = currentCourse.getCode();

        // This course's prerequisite chain was already checked.
        if (checked.count(currentCode) != 0)
        {
            return;
        }

        // Returning to a course still being checked means a cycle.
        if (checking.count(currentCode) != 0)
        {
            throw PrerequisiteNotMetException(
                "Cannot enrol: prerequisite cycle detected at " +
                currentCode + "."
            );
        }

        checking.insert(currentCode);

        for (const std::string& prerequisiteCode :
             currentCourse.getPrerequisites())
        {
            if (!hasCompleted(prerequisiteCode))
            {
                throw PrerequisiteNotMetException(
                    "Cannot enrol: complete " +
                    prerequisiteCode + " first."
                );
            }

            if (application == nullptr)
            {
                throw PrerequisiteNotMetException(
                    "Cannot check prerequisites: "
                    "student is not connected to the application."
                );
            }

            Course* prerequisite =
                application->findCourse(prerequisiteCode);

            if (prerequisite == nullptr)
            {
                throw PrerequisiteNotMetException(
                    "Cannot check prerequisites: course " +
                    prerequisiteCode + " was not found."
                );
            }

            // Check the required course's own prerequisites.
            checkPrerequisites(*prerequisite);
        }

        checking.erase(currentCode);
        checked.insert(currentCode);
    };

    checkPrerequisites(course);

    if (timetable.hasClash(course))
    {
        throw TimetableClashException(
            "Cannot enrol: timetable clash detected."
        );
    }

    const std::time_t now = std::time(nullptr);

    std::ostringstream date;
    date << std::put_time(
        std::localtime(&now),
        "%Y-%m-%d"
    );

    auto enrolment = std::make_unique<Enrolment>(
        *this,
        course,
        "Enrolled",
        date.str(),
        0
    );

    // The student owns the enrolment.
    enrolments.push_back(std::move(enrolment));

    // The course refers to that same enrolment.
    course.addEnrolment(*enrolments.back());

    timetable.addCourse(course);
}

void Student::dropCourse(Course& course)
{
    for (const auto& enrolment : enrolments)
    {
        if (enrolment->getCourse() == &course &&
            enrolment->status == "Enrolled")
        {
            enrolment->status = "Dropped";

            course.removeEnrolment(*enrolment);
            timetable.removeCourse(course);

            return;
        }
    }

    throw NotEnrolledException(
        "Cannot drop: student is not enrolled in this course."
    );
}
bool Student::hasCompleted(const string& courseCode) const
{
    for (const auto& enrolment : enrolments)
    {
        if (enrolment->getCourse()->getCode() == courseCode &&
            enrolment->isCompleted())
        {
            return true;
        }
    }

    return false;
}

bool Student::isEnrolled(const Course& course) const
{
    for (const auto& enrolment : enrolments)
    {
        if (enrolment->getCourse() == &course &&
            enrolment->status == "Enrolled")
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