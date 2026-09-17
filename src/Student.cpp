#include "Student.h"
#include "Course.h"

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
    cout << "\n===== Student Menu (" << getName() << ") =====\n";
    cout << "1. Enroll in a course\n";
    cout << "2. Drop a course\n";
    cout << "3. View my timetable\n";
    cout << "4. Check course completion\n";
    cout << "0. Logout\n";
    // Reading the choice and dispatching to the functions below is wired
    // up by the Menu/UI layer (Phase 9) - this only defines what the
    // student sees, satisfying FR1.3's polymorphic-menu requirement.
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
    os << "Student [Name: " << s.getName()
       << ", ID: " << s.getId() << "]";
    return os;
}