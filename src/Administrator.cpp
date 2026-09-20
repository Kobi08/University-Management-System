#include "Administrator.h"
#include "Menu.h"
#include "Student.h"
#include "Lecturer.h"
#include "Course.h"
#include "Enrolment.h"
#include "Exceptions.h"

#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimeSlot.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

namespace
{
    list<string> parsePrerequisites(
        const string& text)
    {
        list<string> result;

        if (text.empty() ||
            text == "-")
        {
            return result;
        }

        istringstream input(text);

        string code;

        while (getline(input, code, ','))
        {
            code.erase(
                remove_if(
                    code.begin(),
                    code.end(),
                    [](unsigned char c)
                    {
                        return isspace(c);
                    }
                ),
                code.end()
            );

            if (code.empty())
            {
                throw Exception(
                    "Invalid prerequisite list."
                );
            }

            result.push_back(code);
        }

        return result;
    }
}

Administrator::Administrator(const string& name,
                             const string& password)
    : Person(name, password)
{
}

Administrator::Administrator(const string& name,
                             const string& password,
                             const string& id)
    : Person(name, password, id)
{
}

void Administrator::showMenu()
{
    if (application == nullptr)
    {
        cout << "Administrator is not connected to the application.\n";
        return;
    }

    int choice = -1;

    do
    {
        try
        {
            cout << "\n===== ADMINISTRATOR MENU =====\n";
            cout << "Administrator: "
                 << getName()
                 << " ("
                 << getId()
                 << ")\n\n";

            cout << "1. Create user\n";
            cout << "2. Update user\n";
            cout << "3. Remove user\n";
            cout << "4. Create course\n";
            cout << "5. Edit course\n";
            cout << "6. Remove course\n";
            cout << "7. Generate enrolment report\n";
            cout << "0. Logout\n";

            choice = application->number(
                "\nEnter choice: ",
                0,
                7
            );

            switch (choice)
            {
                case 1:
                {
                    string name =
                        application->ask("Name: ");

                    string id =
                        application->ask(
                            "User ID (example U005): "
                        );

                    cout << "\n1. Student\n";
                    cout << "2. Lecturer\n";
                    cout << "3. Administrator\n";

                    int roleChoice =
                        application->number(
                            "Role: ",
                            1,
                            3
                        );

                    string role;

                    if (roleChoice == 1)
                    {
                        role = "Student";
                    }
                    else if (roleChoice == 2)
                    {
                        role = "Lecturer";
                    }
                    else
                    {
                        role = "Administrator";
                    }

                    createUser(
                        name,
                        id,
                        role
                    );

                    break;
                }

                case 2:
                {
                    string id =
                        application->ask(
                            "User ID to update: "
                        );

                    string newName =
                        application->ask(
                            "New name: "
                        );

                    string newPassword =
                        application->ask(
                            "New password: "
                        );

                    updateUser(
                        id,
                        newName,
                        newPassword
                    );

                    break;
                }

                case 3:
                {
                    string id =
                        application->ask(
                            "User ID to remove: "
                        );

                    if (removeUser(id))
                    {
                        cout << "User removed successfully.\n";
                    }

                    break;
                }

              case 4:
{
    string code =
        application->ask(
            "Course code: "
        );

    string title =
        application->ask(
            "Course title: "
        );

    int credits =
        application->number(
            "Credits: ",
            1,
            30
        );

    int capacity =
        application->number(
            "Capacity: ",
            1,
            10000
        );

    string lecturerId =
        application->ask(
            "Lecturer ID: "
        );

    Lecturer* lecturer =
        dynamic_cast<Lecturer*>(
            application->findUser(
                lecturerId
            )
        );

    if (lecturer == nullptr)
    {
        throw Exception(
            "Lecturer not found: " +
            lecturerId
        );
    }

    string prerequisiteInput =
        application->ask(
            "Prerequisites "
            "(comma separated or -): "
        );

    list<string> prerequisites =
        parsePrerequisites(
            prerequisiteInput
        );

    cout << "\n1. Lecture\n";
    cout << "2. Lab\n";
    cout << "3. Project\n";

    int typeChoice =
        application->number(
            "Course type: ",
            1,
            3
        );

    string courseType;

    if (typeChoice == 1)
    {
        courseType = "Lecture";
    }
    else if (typeChoice == 2)
    {
        courseType = "Lab";
    }
    else
    {
        courseType = "Project";
    }

    if (!createCourse(
            code,
            title,
            credits,
            capacity,
            *lecturer,
            prerequisites,
            courseType))
    {
        throw Exception(
            "Course could not be created."
        );
    }

    Course* created =
        application->findCourse(
            code
        );

    if (created == nullptr)
    {
        throw Exception(
            "Created course could not be found."
        );
    }

    string day =
        application->ask(
            "Day: "
        );

    int startTime =
        application->number(
            "Start hour (0-23): ",
            0,
            23
        );

    int endTime =
        application->number(
            "End hour (1-24): ",
            1,
            24
        );

    if (startTime >= endTime)
    {
        throw Exception(
            "Start time must be before end time."
        );
    }

    string location =
        application->ask(
            "Location: "
        );

    created->addTimeSlot(
        TimeSlot(
            day,
            startTime,
            endTime,
            location
        )
    );

    application->save();

    cout << "Course created successfully.\n";

    break;
}

                case 5:
{
    string code =
        application->ask(
            "Course code to edit: "
        );

    Course* existing =
        application->findCourse(
            code
        );

    if (existing == nullptr)
    {
        throw Exception(
            "Course not found: " +
            code
        );
    }

    string newCode =
        application->ask(
            "New course code: "
        );

    string newTitle =
        application->ask(
            "New title: "
        );

    int newCredits =
        application->number(
            "New credits: ",
            1,
            30
        );

    int newCapacity =
        application->number(
            "New capacity: ",
            1,
            10000
        );

    string lecturerId =
        application->ask(
            "New lecturer ID: "
        );

    Lecturer* lecturer =
        dynamic_cast<Lecturer*>(
            application->findUser(
                lecturerId
            )
        );

    if (lecturer == nullptr)
    {
        throw Exception(
            "Lecturer not found: " +
            lecturerId
        );
    }

    string prerequisiteInput =
        application->ask(
            "New prerequisites "
            "(comma separated or -): "
        );

    list<string> prerequisites =
        parsePrerequisites(
            prerequisiteInput
        );

    cout << "\n1. Lecture\n";
    cout << "2. Lab\n";
    cout << "3. Project\n";

    int typeChoice =
        application->number(
            "New course type: ",
            1,
            3
        );

    string courseType;

    if (typeChoice == 1)
    {
        courseType = "Lecture";
    }
    else if (typeChoice == 2)
    {
        courseType = "Lab";
    }
    else
    {
        courseType = "Project";
    }

    editCourse(
        code,
        newCode,
        newTitle,
        newCredits,
        newCapacity,
        *lecturer,
        prerequisites,
        courseType
    );

    cout << "Course updated successfully.\n";

    break;
}

              case 6:
{
    string code =
        application->ask(
            "Course code to remove: "
        );

    string removedCode =
        removeCourse(code);

    if (!removedCode.empty())
    {
        cout << "Course "
             << removedCode
             << " removed successfully.\n";
    }

    break;
}
                case 7:
                {
                    generateEnrolmentReport();
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

void Administrator::createUser(const string& name,
                               const string& id,
                               const string& role)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected to the application."
        );
    }

    if (name.empty())
    {
        throw Exception(
            "User name cannot be empty."
        );
    }

    if (id.size() < 2 ||
        id[0] != 'U')
    {
        throw Exception(
            "User ID must use the format U001, U002, etc."
        );
    }

    const bool numericId =
        std::all_of(
            id.begin() + 1,
            id.end(),
            [](unsigned char character)
            {
                return std::isdigit(character);
            }
        );

    if (!numericId)
    {
        throw Exception(
            "User ID must use the format U001, U002, etc."
        );
    }

    if (application->findUser(id) != nullptr)
    {
        throw Exception(
            "A user with ID " +
            id +
            " already exists."
        );
    }

    // Existing UML createUser() does not contain a password
    // parameter, so new accounts receive an initial password.
    const string defaultPassword = "1234";

    unique_ptr<Person> newUser;

    if (role == "Student")
    {
        newUser =
            make_unique<Student>(
                name,
                defaultPassword,
                id
            );
    }
    else if (role == "Lecturer")
    {
        newUser =
            make_unique<Lecturer>(
                name,
                defaultPassword,
                id
            );
    }
    else if (role == "Administrator")
    {
        newUser =
            make_unique<Administrator>(
                name,
                defaultPassword,
                id
            );
    }
    else
    {
        throw Exception(
            "Invalid user role."
        );
    }

    newUser->setApplication(application);

    application->users.push_back(
        std::move(newUser)
    );

    application->save();

    cout << "User created successfully.\n";
    cout << "User ID: "
         << id
         << '\n';

    cout << "Initial password: "
         << defaultPassword
         << '\n';
}

void Administrator::updateUser(const string& id,
                               const string& newName,
                               const string& newPass)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected to the application."
        );
    }

    Person* target =
        application->findUser(id);

    if (target == nullptr)
    {
        throw Exception(
            "User not found: " +
            id
        );
    }

    if (newName.empty())
    {
        throw Exception(
            "Name cannot be empty."
        );
    }

    if (newPass.empty())
    {
        throw Exception(
            "Password cannot be empty."
        );
    }

    // Administrator is a friend of Person.
    target->name = newName;
    target->password = newPass;

    application->save();

    cout << "User updated successfully.\n";
}

bool Administrator::removeUser(const string& id)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected to the application."
        );
    }

    Person* target =
        application->findUser(id);

    if (target == nullptr)
    {
        throw Exception(
            "User not found: " +
            id
        );
    }

    if (target == this)
    {
        throw Exception(
            "You cannot remove the currently logged-in administrator."
        );
    }

    if (application->userReferenced(target))
    {
        throw Exception(
            "Cannot remove user because the user is "
            "referenced by courses or enrolment history."
        );
    }

    auto& users =
        application->users;

    users.erase(
        std::remove_if(
            users.begin(),
            users.end(),
            [target](const unique_ptr<Person>& user)
            {
                return user.get() == target;
            }
        ),
        users.end()
    );

    application->save();

    return true;
}

bool Administrator::createCourse(
    const string& code,
    const string& title,
    int credits,
    int capacity,
    Lecturer& assignedLecturer,
    const list<string>& prerequisites,
    const string& courseType)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected "
            "to the application."
        );
    }

    if (code.empty() ||
        title.empty())
    {
        throw Exception(
            "Course code and title "
            "cannot be empty."
        );
    }

    if (credits <= 0 ||
        capacity <= 0)
    {
        throw Exception(
            "Credits and capacity "
            "must be positive."
        );
    }

    if (application->findCourse(code)
        != nullptr)
    {
        throw Exception(
            "Course already exists: " +
            code
        );
    }

    for (const string& prerequisite :
         prerequisites)
    {
        if (prerequisite == code)
        {
            throw Exception(
                "A course cannot be "
                "its own prerequisite."
            );
        }

        if (application->findCourse(
                prerequisite) == nullptr)
        {
            throw Exception(
                "Prerequisite course not found: " +
                prerequisite
            );
        }
    }

    unique_ptr<Course> course;

    if (courseType == "Lecture")
    {
        course =
            make_unique<LectureCourse>(
                code,
                title,
                credits,
                capacity,
                assignedLecturer,
                prerequisites
            );
    }
    else if (courseType == "Lab")
    {
        course =
            make_unique<LabCourse>(
                code,
                title,
                credits,
                capacity,
                assignedLecturer,
                prerequisites
            );
    }
    else if (courseType == "Project")
    {
        course =
            make_unique<ProjectCourse>(
                code,
                title,
                credits,
                capacity,
                assignedLecturer,
                prerequisites
            );
    }
    else
    {
        throw Exception(
            "Invalid course type."
        );
    }

    Course* coursePtr =
        course.get();

    application->courses.push_back(
        std::move(course)
    );

    assignedLecturer.addCourse(
        *coursePtr
    );

    return true;
}

void Administrator::editCourse(
    const string& code,
    const string& newCode,
    const string& newTitle,
    int newCredits,
    int newCapacity,
    Lecturer& newAssignedLecturer,
    const list<string>& newPrerequisites,
    const string& newCourseType)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected "
            "to the application."
        );
    }

    Course* course =
        application->findCourse(
            code
        );

    if (course == nullptr)
    {
        throw Exception(
            "Course not found: " +
            code
        );
    }

    if (newCode.empty() ||
        newTitle.empty())
    {
        throw Exception(
            "Course code and title "
            "cannot be empty."
        );
    }

    if (newCredits <= 0 ||
        newCapacity <= 0)
    {
        throw Exception(
            "Credits and capacity "
            "must be positive."
        );
    }

    if (newCode != code &&
        application->findCourse(newCode)
            != nullptr)
    {
        throw Exception(
            "Another course already uses code " +
            newCode
        );
    }

    for (const string& prerequisite :
         newPrerequisites)
    {
        if (prerequisite == code ||
            prerequisite == newCode)
        {
            throw Exception(
                "A course cannot be "
                "its own prerequisite."
            );
        }

        if (application->findCourse(
                prerequisite) == nullptr)
        {
            throw Exception(
                "Prerequisite course not found: " +
                prerequisite
            );
        }
    }

    if (newCourseType != "Lecture" &&
        newCourseType != "Lab" &&
        newCourseType != "Project")
    {
        throw Exception(
            "Invalid course type."
        );
    }

    const string oldCode =
        course->code;

    Lecturer* oldLecturer =
        course->asignlecturer;

    // -------------------------------------------------
    // Same derived type: update the existing object.
    // This preserves Enrolment/Timetable pointers.
    // -------------------------------------------------

    if (course->getCourseType()
        == newCourseType)
    {
        if (oldLecturer !=
            &newAssignedLecturer)
        {
            if (oldLecturer != nullptr)
            {
                oldLecturer->
                    assignedCourse.remove(
                        course
                    );
            }

            newAssignedLecturer.addCourse(
                *course
            );
        }

        course->code =
            newCode;

        course->title =
            newTitle;

        course->credit =
            newCredits;

        course->capacity =
            newCapacity;

        course->asignlecturer =
            &newAssignedLecturer;

        course->prerequisites =
            newPrerequisites;
    }

    // -------------------------------------------------
    // Different derived type.
    // Replacing the object is only safe when students
    // do not already have enrolment records pointing
    // at the existing Course object.
    // -------------------------------------------------

    else
    {
        for (const auto& user :
             application->users)
        {
            Student* student =
                dynamic_cast<Student*>(
                    user.get()
                );

            if (student == nullptr)
            {
                continue;
            }

            for (const auto& enrolment :
                 student->enrolments)
            {
                if (enrolment != nullptr &&
                    enrolment->getCourse()
                        == course)
                {
                    throw Exception(
                        "Cannot change the course type "
                        "because enrolment history "
                        "already references this course."
                    );
                }
            }
        }

        unique_ptr<Course> replacement;

        if (newCourseType == "Lecture")
        {
            replacement =
                make_unique<LectureCourse>(
                    newCode,
                    newTitle,
                    newCredits,
                    newCapacity,
                    newAssignedLecturer,
                    newPrerequisites
                );
        }
        else if (newCourseType == "Lab")
        {
            replacement =
                make_unique<LabCourse>(
                    newCode,
                    newTitle,
                    newCredits,
                    newCapacity,
                    newAssignedLecturer,
                    newPrerequisites
                );
        }
        else
        {
            replacement =
                make_unique<ProjectCourse>(
                    newCode,
                    newTitle,
                    newCredits,
                    newCapacity,
                    newAssignedLecturer,
                    newPrerequisites
                );
        }

        // Preserve existing time slots.
        for (const TimeSlot& slot :
             course->timeslot)
        {
            replacement->addTimeSlot(
                slot
            );
        }

        if (oldLecturer != nullptr)
        {
            oldLecturer->
                assignedCourse.remove(
                    course
                );
        }

        Course* replacementPtr =
            replacement.get();

        bool replaced = false;

        for (auto& owner :
             application->courses)
        {
            if (owner.get() == course)
            {
                owner =
                    std::move(
                        replacement
                    );

                replaced = true;
                break;
            }
        }

        if (!replaced)
        {
            throw Exception(
                "Unable to replace course."
            );
        }

        newAssignedLecturer.addCourse(
            *replacementPtr
        );

        course =
            replacementPtr;
    }

    // If the course code changed, update prerequisite
    // strings in all other courses.
    if (oldCode != newCode)
    {
        for (auto& other :
             application->courses)
        {
            if (other == nullptr ||
                other.get() == course)
            {
                continue;
            }

            for (string& prerequisite :
                 other->prerequisites)
            {
                if (prerequisite ==
                    oldCode)
                {
                    prerequisite =
                        newCode;
                }
            }
        }
    }

    application->save();
}

string Administrator::removeCourse(
    const string& code)
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected "
            "to the application."
        );
    }

    Course* course =
        application->findCourse(
            code
        );

    if (course == nullptr)
    {
        throw Exception(
            "Course not found: " +
            code
        );
    }

    if (application->courseReferenced(
            course))
    {
        throw Exception(
            "Cannot remove course because "
            "enrolment history or another "
            "course prerequisite references it."
        );
    }

    Lecturer* lecturer =
        course->asignlecturer;

    if (lecturer != nullptr)
    {
        lecturer->assignedCourse.remove(
            course
        );
    }

    for (auto it =
             application->courses.begin();
         it !=
             application->courses.end();
         ++it)
    {
        if (it->get() == course)
        {
            application->courses.erase(
                it
            );

            application->save();

            return code;
        }
    }

    throw Exception(
        "Unable to remove course."
    );
}

void Administrator::generateEnrolmentReport()
{
    if (application == nullptr)
    {
        throw Exception(
            "Administrator is not connected to the application."
        );
    }

    cout << "\n===== ENROLMENT REPORT =====\n";

    if (application->courses.empty())
    {
        cout << "No courses available.\n";
        return;
    }

    for (const auto& courseOwner :
         application->courses)
    {
        if (courseOwner == nullptr)
        {
            continue;
        }

        Course* course =
            courseOwner.get();

        const list<Enrolment*> enrolments =
            course->viewEnrolment();

        cout << "\nCourse: "
             << course->getCode()
             << '\n';

        cout << "Type: "
             << course->getCourseType()
             << '\n';

        cout << "Enrolment count: "
             << enrolments.size()
             << '\n';

        if (enrolments.empty())
        {
            cout << "  No enrolments.\n";
            continue;
        }

        for (Enrolment* enrolment :
             enrolments)
        {
            if (enrolment == nullptr)
            {
                continue;
            }

            Student* student =
                enrolment->getStudent();

            if (student == nullptr)
            {
                continue;
            }

            cout << "  "
                 << student->getId()
                 << " - "
                 << student->getName();

            if (enrolment->isCompleted())
            {
                cout << " | Completed"
                     << " | Grade: "
                     << enrolment->getGrade();
            }
            else
            {
                cout << " | Enrolled";
            }

            cout << '\n';
        }
    }

    cout << "\n===== END OF REPORT =====\n";
}