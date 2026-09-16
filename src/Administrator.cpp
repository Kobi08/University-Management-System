#include "Administrator.h"
#include "Lecturer.h"

#include <iostream>

using namespace std;

Administrator::Administrator(const string& name,
                             const string& password)
    : Person(name, password)
{
}

void Administrator::showMenu()
{
    cout << "\n===== Administrator Menu ("
         << getName() << ") =====\n";

    cout << "1. Create user\n";
    cout << "2. Update user\n";
    cout << "3. Remove user\n";
    cout << "4. Create course\n";
    cout << "5. Edit course\n";
    cout << "6. Remove course\n";
    cout << "7. Generate enrolment report\n";
    cout << "0. Logout\n";
}

void Administrator::createUser(const string& name,
                               const string& id,
                               const string& role)
{
    // Repository / user management will be connected later.
}

void Administrator::updateUser(const string& id,
                               const string& newName,
                               const string& newPass)
{
    // Repository / user management will be connected later.
}

bool Administrator::removeUser(const string& id)
{
    // Repository / user management will be connected later.
    return false;
}

bool Administrator::createCourse(const string& code,
                                 const string& title,
                                 int credits,
                                 int capacity,
                                 Lecturer& assignedLecturer,
                                 const list<string>& prerequisites,
                                 const string& courseType)
{
    // Course creation will be connected to the
    // repository and course hierarchy later.

    return false;
}

void Administrator::editCourse(const string& code,
                               const string& newCode,
                               const string& newTitle,
                               int newCredits,
                               int newCapacity,
                               Lecturer& newAssignedLecturer,
                               const list<string>& newPrerequisites,
                               const string& newCourseType)
{
    // Course editing will be connected later.
}

string Administrator::removeCourse(const string& code)
{
    // Course removal will be connected later.
    return "";
}

void Administrator::generateEnrolmentReport()
{
    // Enrolment repository/report generation will be connected later.
}

ostream& operator<<(ostream& os,
                    const Administrator& administrator)
{
    os << "Administrator [Name: "
       << administrator.getName()
       << ", ID: "
       << administrator.getId()
       << "]";

    return os;
}