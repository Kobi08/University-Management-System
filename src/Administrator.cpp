#include "Administrator.h"

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

    // TODO: Menu choice handling will be connected by the Menu/UI layer.
}

void Administrator::createUser(const string& name,
                               const string& id,
                               const string& role)
{
    // TODO: Implement user creation using the required
    // Student, Lecturer and Administrator classes.

    (void)name;
    (void)id;
    (void)role;
}

void Administrator::updateUser(const string& id,
                               const string& newName,
                               const string& newPass)
{
    // TODO: Implement user update when the required
    // user-management functionality is available.

    (void)id;
    (void)newName;
    (void)newPass;
}

bool Administrator::removeUser(const string& id)
{
    // TODO: Implement user removal when the required
    // user-management functionality is available.

    (void)id;
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
    // TODO: Implement course creation using the final
    // Course hierarchy and assigned Lecturer.

    (void)code;
    (void)title;
    (void)credits;
    (void)capacity;
    (void)assignedLecturer;
    (void)prerequisites;
    (void)courseType;

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
    // TODO: Implement course editing using the final
    // Course hierarchy and assigned Lecturer.

    (void)code;
    (void)newCode;
    (void)newTitle;
    (void)newCredits;
    (void)newCapacity;
    (void)newAssignedLecturer;
    (void)newPrerequisites;
    (void)newCourseType;
}

string Administrator::removeCourse(const string& code)
{
    // TODO: Implement course removal using the final
    // Course hierarchy.

    (void)code;
    return "";
}

void Administrator::generateEnrolmentReport()
{
    // TODO: Implement enrolment report generation once
    // the final Enrolment and reporting functionality is available.
}