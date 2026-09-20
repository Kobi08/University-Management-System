#include "Student.h"
#include "Course.h"
#include "Person.h"
#include <limits>
#include <stdexcept>

using namespace std;

Student::Student(const string& name, const string& password)
    : Person(name, password), timetable() {}

Student::Student(const string& name,
                 const string& password,
                 const string& id)
    : Person(name, password, id),
      timetable()
{
}

void Student::showMenu()
{
    int choice=-1;

    do
    {
        cout << "\n===== Student Menu (" << getName() << ") =====\n";
        cout << "1. View Timetable\n";
        cout << "2. Enroll Course\n";
        cout << "3. Drop Course\n";
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
            viewTimetable();
            break;

        case 2:
            cout << "Enroll Course integration coming next.\n";
            break;

        case 3:
            cout << "Drop Course integration coming next.\n";
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

void Student::enrollCourse(Course& course)
{
    if (isEnrolled(course))
    {
        return;
    }

    // TODO (Phase 5): prerequisite chain check (FR3.2/FR3.4), capacity
    // check (FR3.2) and timetable clash check (FR4.2) must run here,
    // each signalled by a distinct custom exception (FR3.3). An
    // Enrolment object also needs to be created once Enrolment exists
    // (Phase 2 step 9) and registered with the Course.
    timetable.addCourse(course);
}

void Student::dropCourse(Course& course)
{
    timetable.removeCourse(course);
    // TODO (Phase 5): update/retire the associated Enrolment record
    // once Enrolment exists.
}

bool Student::hasCompleted(const string& courseCode) const
{
    // TODO (Phase 2 step 9 / Phase 5): this requires checking this
    // student's Enrolment records for a "completed" status against
    // courseCode. Enrolment does not exist yet, so this cannot be
    // truthfully implemented - returning false is a placeholder, not
    // a design decision.
    (void)courseCode;
    return false;
}

bool Student::isEnrolled(const Course& course) const
{
    for (Course* c : timetable.getCourses())
    {
        if (c == &course)
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

ostream& operator<<(ostream& os, const Student& s)
{
    os << s.getId() << "|" << s.getName() << "|" << s.getPassword();
    return os;
}