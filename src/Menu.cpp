#include "Menu.h"
#include "Exceptions.h"
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"

#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "Enrolment.h"

#include "TimeSlot.h"

#include <iostream>
#include <sstream>
#include "Repository.h"
#include <unordered_set>

Menu::Menu(const std::string& path)
    : dataPath(path)
{
}

Menu::~Menu() = default;

void Menu::run()
{
    try
    {
        // Temporary until full persistence is connected.
       loadUsers();
       loadCourses();
       loadEnrolments();


        while (!stop)
        {
            showloginmenu();

            std::string id = ask("User ID: ");

            if (id == "0")
            {
                stop = true;
                std::cout << "Application closed.\n";
                break;
            }

            std::string password = ask("Password: ");

            Person* currentUser = findUser(id);

            if (currentUser == nullptr ||
                !currentUser->login(password))
            {
                std::cout
                    << "Invalid user ID or password.\n";

                continue;
            }

            current = currentUser;

            std::cout << "\nWelcome, "
                      << currentUser->getName()
                      << "!\n";

            // THIS is the important polymorphic call.
            currentUser->showMenu();

            current = nullptr;
        }
    }
    catch (const Exception& error)
    {
        std::cout << "Application error: "
                  << error.what()
                  << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "Application error: "
                  << error.what()
                  << '\n';
    }
}

void Menu::loadUsers()
{
    users.clear();

    Repository<std::string> studentRepository(
        "data/students.txt"
    );

    Repository<std::string> lecturerRepository(
        "data/lecturers.txt"
    );

    Repository<std::string> administratorRepository(
        "data/administrators.txt"
    );

    std::unordered_set<std::string> usedIds;

    auto splitUserRow =
        [](const std::string& row,
           std::string& id,
           std::string& name,
           std::string& password)
    {
        std::istringstream input(row);

 if (!std::getline(input, id, '|') ||
    !std::getline(input, name, '|') ||
    !std::getline(input, password, '|'))
{
    throw CorruptDataException(
        "Invalid user record: " + row
    );
}

std::string extra;

if (std::getline(input, extra, '|'))
{
    throw CorruptDataException(
        "Too many fields in user record: " + row
    );
}

        if (id.empty() ||
            name.empty() ||
            password.empty())
        {
            throw CorruptDataException(
                "Incomplete user record: " + row
            );
        }
    };

    // ---------- STUDENTS ----------
    for (const std::string& row :
         studentRepository.load())
    {
        std::string id;
        std::string name;
        std::string password;

        splitUserRow(
            row,
            id,
            name,
            password
        );

        if (!usedIds.insert(id).second)
        {
            throw CorruptDataException(
                "Duplicate user ID: " + id
            );
        }

        auto student =
            std::make_unique<Student>(
                name,
                password,
                id
            );

        student->setApplication(this);

        users.push_back(
            std::move(student)
        );
    }

    // ---------- LECTURERS ----------
    for (const std::string& row :
         lecturerRepository.load())
    {
        std::string id;
        std::string name;
        std::string password;

        splitUserRow(
            row,
            id,
            name,
            password
        );

        if (!usedIds.insert(id).second)
        {
            throw CorruptDataException(
                "Duplicate user ID: " + id
            );
        }

        auto lecturer =
            std::make_unique<Lecturer>(
                name,
                password,
                id
            );

        lecturer->setApplication(this);

        users.push_back(
            std::move(lecturer)
        );
    }

    // ---------- ADMINISTRATORS ----------
    for (const std::string& row :
         administratorRepository.load())
    {
        std::string id;
        std::string name;
        std::string password;

        splitUserRow(
            row,
            id,
            name,
            password
        );

        if (!usedIds.insert(id).second)
        {
            throw CorruptDataException(
                "Duplicate user ID: " + id
            );
        }

        auto administrator =
            std::make_unique<Administrator>(
                name,
                password,
                id
            );

        administrator->setApplication(this);

        users.push_back(
            std::move(administrator)
        );
    }
}

void Menu::loadCourses()
{
    courses.clear();

    Repository<std::string> courseRepository(
        "data/courses.txt"
    );

    for (const std::string& row :
         courseRepository.load())
    {
        std::istringstream input(row);

        std::string type;
        std::string code;
        std::string title;
        std::string creditText;
        std::string capacityText;
        std::string lecturerId;

        if (!std::getline(input, type, '|') ||
            !std::getline(input, code, '|') ||
            !std::getline(input, title, '|') ||
            !std::getline(input, creditText, '|') ||
            !std::getline(input, capacityText, '|') ||
            !std::getline(input, lecturerId, '|'))
        {
            throw CorruptDataException(
                "Invalid course record: " + row
            );
        }

        if (type.empty() ||
            code.empty() ||
            title.empty() ||
            creditText.empty() ||
            capacityText.empty() ||
            lecturerId.empty())
        {
            throw CorruptDataException(
                "Incomplete course record: " + row
            );
        }

        int credit;
        int capacity;

        try
        {
            credit = std::stoi(creditText);
            capacity = std::stoi(capacityText);
        }
        catch (...)
        {
            throw CorruptDataException(
                "Invalid numeric value in course: " + row
            );
        }

        Person* person = findUser(lecturerId);

        Lecturer* lecturer =
            dynamic_cast<Lecturer*>(person);

        if (lecturer == nullptr)
        {
            throw CorruptDataException(
                "Lecturer not found for course " +
                code + ": " + lecturerId
            );
        }

        std::unique_ptr<Course> course;

        if (type == "Lecture")
        {
            course =
                std::make_unique<LectureCourse>(
                    code,
                    title,
                    credit,
                    capacity,
                    *lecturer
                );
        }
        else if (type == "Lab")
        {
            course =
                std::make_unique<LabCourse>(
                    code,
                    title,
                    credit,
                    capacity,
                    *lecturer
                );
        }
        else if (type == "Project")
        {
            course =
                std::make_unique<ProjectCourse>(
                    code,
                    title,
                    credit,
                    capacity,
                    *lecturer
                );
        }
        else
        {
            throw CorruptDataException(
                "Unknown course type: " + type
            );
        }

        // Lecturer aggregates/reference the same course.
        lecturer->addCourse(*course);

        // Menu/application owns the course.
        courses.push_back(
            std::move(course)
        );
    }
}
void Menu::createDemo()
{
    if (!users.empty())
    {
        return;
    }

    auto student = std::make_unique<Student>(
        "Demo Student",
        "student123"
    );

    auto lecturer = std::make_unique<Lecturer>(
        "Demo Lecturer",
        "lecturer123"
    );

    auto administrator =
        std::make_unique<Administrator>(
            "Demo Administrator",
            "admin123"
        );

    student->setApplication(this);
    lecturer->setApplication(this);
    administrator->setApplication(this);

    Lecturer* lecturerPtr = lecturer.get();

    users.push_back(std::move(student));
    users.push_back(std::move(lecturer));
    users.push_back(std::move(administrator));

    auto oopCourse =
        std::make_unique<LectureCourse>(
            "CO2203",
            "Object Oriented Programming",
            3,
            50,
            *lecturerPtr
        );

    oopCourse->addTimeSlot(
        TimeSlot(
            "Monday",
            9,
            11,
            "Lecture Hall 1"
        )
    );

    lecturerPtr->addCourse(*oopCourse);

    courses.push_back(std::move(oopCourse));
}

void Menu::showloginmenu()
{
    std::cout << "\n========================================\n";
    std::cout << " UNIVERSITY MANAGEMENT SYSTEM\n";
    std::cout << "========================================\n";
    std::cout << "Enter 0 as the User ID to exit.\n";
}

void Menu::loadEnrolments()
{
    Repository<std::string> enrolmentRepository(
        "data/enrolments.txt"
    );

    for (const std::string& row :
         enrolmentRepository.load())
    {
        std::istringstream input(row);

        std::string studentId;
        std::string courseCode;
        std::string status;
        std::string dateEnrolled;
        std::string gradeText;

        if (!std::getline(input, studentId, '|') ||
            !std::getline(input, courseCode, '|') ||
            !std::getline(input, status, '|') ||
            !std::getline(input, dateEnrolled, '|') ||
            !std::getline(input, gradeText, '|'))
        {
            throw CorruptDataException(
                "Invalid enrolment record: " + row
            );
        }

        if (studentId.empty() ||
            courseCode.empty() ||
            status.empty() ||
            dateEnrolled.empty() ||
            gradeText.empty())
        {
            throw CorruptDataException(
                "Incomplete enrolment record: " + row
            );
        }

        double grade;

        try
        {
            grade = std::stod(gradeText);
        }
        catch (...)
        {
            throw CorruptDataException(
                "Invalid grade in enrolment record: " + row
            );
        }

        Person* person = findUser(studentId);

        Student* student =
            dynamic_cast<Student*>(person);

        if (student == nullptr)
        {
            throw CorruptDataException(
                "Student not found: " + studentId
            );
        }

        Course* course =
            findCourse(courseCode);

        if (course == nullptr)
        {
            throw CorruptDataException(
                "Course not found: " + courseCode
            );
        }

        auto enrolment =
            std::make_unique<Enrolment>(
                *student,
                *course,
                status,
                dateEnrolled,
                grade
            );

        Enrolment* enrolmentPtr =
            enrolment.get();

        student->enrolments.push_back(
            std::move(enrolment)
        );

        // Active/completed enrolments are visible
        // from the course side.
        if (status != "Dropped")
        {
            course->addEnrolment(
                *enrolmentPtr
            );
        }

        // Only currently enrolled courses belong
        // in the student's active timetable.
        if (status == "Enrolled")
        {
            student->timetable.addCourse(
                *course
            );
        }
    }
}

int Menu::number(const std::string& prompt,
                 int low,
                 int high)
{
    const std::string text = ask(prompt);

    std::istringstream input(text);
    int value;

    if (!(input >> value))
    {
        throw Exception("Enter a whole number.");
    }

    // Allow trailing spaces, but reject extra text.
    input >> std::ws;

    if (!input.eof())
    {
        throw Exception(
            "Enter a whole number without extra characters."
        );
    }

    if (value < low || value > high)
    {
        throw Exception(
            "Enter a number between " +
            std::to_string(low) + " and " +
            std::to_string(high) + "."
        );
    }

    return value;
}

Person* Menu::findUser(const std::string& id) const
{
    for (const auto& user : users)
    {
        if (user->getId() == id)
        {
            return user.get();
        }
    }

    return nullptr;
}

Course* Menu::findCourse(const std::string& code) const
{
    for (const auto& course : courses)
    {
        if (course->getCode() == code)
        {
            return course.get();
        }
    }

    return nullptr;
}

void Menu::listUsers() const
{
    std::cout << "\n===== USERS =====\n";

    if (users.empty())
    {
        std::cout << "No users available.\n";
        return;
    }

    for (const auto& user : users)
    {
        std::cout << "ID: " << user->getId()
                  << " | Name: " << user->getName()
                  << '\n';
    }
}

void Menu::listCourses() const
{
    std::cout << "\n===== COURSES =====\n";

    if (courses.empty())
    {
        std::cout << "No courses available.\n";
        return;
    }

    for (const auto& course : courses)
    {
        std::cout << *course << '\n';

        std::cout << "Type: "
                  << course->getCourseType()
                  << '\n';

        const Lecturer* lecturer = course->getLecturer();

        if (lecturer != nullptr)
        {
            std::cout << "Lecturer: "
                      << lecturer->getId()
                      << " | "
                      << lecturer->getName()
                      << '\n';
        }

        for (const TimeSlot& slot : course->getTimeSlots())
        {
            std::cout << "  " << slot << '\n';
        }

        std::cout << '\n';
    }
}

std::string Menu::ask(const std::string& prompt)
{
    std::cout << prompt;

    std::string value;

    if (!std::getline(std::cin, value))
    {
        throw Exception("Input closed.");
    }

    return value;
}


