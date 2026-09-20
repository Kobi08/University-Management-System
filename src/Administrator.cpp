#include "Administrator.h"
#include "Lecturer.h"
#include "LabCourse.h"
#include "Student.h"
#include <limits>
#include <stdexcept>
#include "Repository.h"
#include <utility>

#include <iostream>

using namespace std;

namespace
{
    template<typename T>
    string saveAndAddUser(
        list<T>& users,
        T newUser,
        const string& filePath)
    {
        list<T> pending;
        pending.push_back(std::move(newUser));

        // Prepare the complete file contents without changing
        // the live collection.
        list<T> snapshot = users;
        snapshot.push_back(pending.front());

        const string newId = pending.front().getId();

        Repository<T> repository(filePath);
        repository.save(snapshot);

        // Transfer the new object into the live collection.
        // Existing user objects remain at their original addresses.
        users.splice(users.end(), pending);

        return newId;
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
    int choice=-1;

    do
    {
        cout << "\n===== Administrator Menu (" << getName() << ") =====\n";
        cout << "1. Create User\n";
        cout << "2. Update User\n";
        cout << "3. Remove User\n";
        cout << "4. Create Course\n";
        cout << "5. Edit Course\n";
        cout << "6. Remove Course\n";
        cout << "7. Generate Report\n";
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
        {
            int type = -1;
            string name;
            string password;
            string role;

            cout << "1. Student\n";
            cout << "2. Lecturer\n";
            cout << "3. Administrator\n";
            cout << "Choose: ";

            if (!(cin >> type))
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

                cout << "Please enter a role number.\n";
                break;
            }

            cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            switch (type)
            {
            case 1:
                role = "Student";
                break;

            case 2:
                role = "Lecturer";
                break;

            case 3:
                role = "Administrator";
                break;

            default:
                cout << "Invalid role. Choose 1, 2, or 3.\n";
                break;
            }

            if (role.empty())
            {
                break;
            }

            cout << "Name: ";

            if (!getline(cin, name))
            {
                return;
            }

            cout << "Password: ";

            if (!getline(cin, password))
            {
                return;
            }

            try
            {
                // createUser() validates the values, saves the account,
                // and adds it to the shared user collection.
                createUser(name, password, role);
            }
            catch (const std::exception& error)
            {
                cout << "Unable to create user: "
                    << error.what()
                    << '\n';
            }

            break;
        }

        case 2:
            cout << "Update User integration coming next.\n";
            break;

        case 3:
            cout << "Remove User integration coming next.\n";
            break;

        case 4:
            cout << "Create Course integration coming next.\n";
            break;

        case 5:
            cout << "Edit Course integration coming next.\n";
            break;

        case 6:
            cout << "Remove Course integration coming next.\n";
            break;

        case 7:
            cout << "Report generation integration coming next.\n";
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
void Administrator::createUser(
    const string& name,
    const string& password,
    const string& role)
{
    if (studentUsers == nullptr ||
        lecturerUsers == nullptr ||
        administratorUsers == nullptr)
    {
        throw runtime_error(
            "User collections have not been connected."
        );
    }

    if (name.find_first_not_of(" \t\r\n") == string::npos ||
        password.empty())
    {
        throw invalid_argument(
            "Name and password cannot be empty."
        );
    }

    if (name.find_first_of("|\r\n") != string::npos ||
        password.find_first_of("| \t\r\n") != string::npos)
    {
        throw invalid_argument(
            "Name cannot contain '|' or line breaks. "
            "Password cannot contain '|' or whitespace."
        );
    }

    string newId;

    if (role == "Student")
    {
        newId = saveAndAddUser(
            *studentUsers,
            Student(name, password),
            "data/students.txt"
        );
    }
    else if (role == "Lecturer")
    {
        newId = saveAndAddUser(
            *lecturerUsers,
            Lecturer(name, password),
            "data/lecturers.txt"
        );
    }
    else if (role == "Administrator")
    {
        Administrator newAdministrator(name, password);

        // A newly created administrator also needs access
        // to the same collections.
        newAdministrator.connectUsers(
            *studentUsers,
            *lecturerUsers,
            *administratorUsers
        );

        newId = saveAndAddUser(
            *administratorUsers,
            std::move(newAdministrator),
            "data/administrators.txt"
        );
    }
    else
    {
        throw invalid_argument("Invalid user role.");
    }

    cout << "\nUser created successfully.\n";
    cout << "User ID: " << newId << '\n';
}

void Administrator::connectUsers(
    list<Student>& students,
    list<Lecturer>& lecturers,
    list<Administrator>& administrators)
{
    studentUsers = &students;
    lecturerUsers = &lecturers;
    administratorUsers = &administrators;
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
    os << administrator.getId() << "|"
       << administrator.getName() << "|"
       << administrator.getPassword();

    return os;
}