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

    std::unordered_set<std::string> usedCourseCodes;

    auto parseInt = [](const std::string& text,
                       const std::string& fieldName,
                       const std::string& row) -> int
    {
        try
        {
            std::size_t position = 0;

            int value = std::stoi(
                text,
                &position
            );

            if (position != text.size())
            {
                throw std::invalid_argument(
                    "extra characters"
                );
            }

            return value;
        }
        catch (...)
        {
            throw CorruptDataException(
                "Invalid " +
                fieldName +
                " in course record: " +
                row
            );
        }
    };

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
        std::string prerequisiteText;
        std::string timeSlotText;

        if (!std::getline(input, type, '|') ||
            !std::getline(input, code, '|') ||
            !std::getline(input, title, '|') ||
            !std::getline(input, creditText, '|') ||
            !std::getline(input, capacityText, '|') ||
            !std::getline(input, lecturerId, '|') ||
            !std::getline(input, prerequisiteText, '|') ||
            !std::getline(input, timeSlotText))
        {
            throw CorruptDataException(
                "Invalid course record: " +
                row
            );
        }

        if (type.empty() ||
            code.empty() ||
            title.empty() ||
            creditText.empty() ||
            capacityText.empty() ||
            lecturerId.empty() ||
            prerequisiteText.empty() ||
            timeSlotText.empty())
        {
            throw CorruptDataException(
                "Incomplete course record: " +
                row
            );
        }

        if (!usedCourseCodes.insert(code).second)
        {
            throw CorruptDataException(
                "Duplicate course code: " +
                code
            );
        }

        const int credit =
            parseInt(
                creditText,
                "credit",
                row
            );

        const int capacity =
            parseInt(
                capacityText,
                "capacity",
                row
            );

        if (credit <= 0 ||
            capacity <= 0)
        {
            throw CorruptDataException(
                "Credit and capacity must be positive "
                "in course record: " +
                row
            );
        }

        Person* person =
            findUser(lecturerId);

        Lecturer* lecturer =
            dynamic_cast<Lecturer*>(person);

        if (lecturer == nullptr)
        {
            throw CorruptDataException(
                "Lecturer not found for course " +
                code +
                ": " +
                lecturerId
            );
        }

        // -----------------------------
        // Load prerequisites
        // -----------------------------

        std::list<std::string> prerequisites;

        if (prerequisiteText != "-")
        {
            std::istringstream prerequisiteStream(
                prerequisiteText
            );

            std::string prerequisiteCode;

            while (std::getline(
                prerequisiteStream,
                prerequisiteCode,
                ','))
            {
                if (prerequisiteCode.empty())
                {
                    throw CorruptDataException(
                        "Invalid prerequisite list "
                        "for course: " +
                        code
                    );
                }

                prerequisites.push_back(
                    prerequisiteCode
                );
            }
        }

        // -----------------------------
        // Create correct course subtype
        // -----------------------------

        std::unique_ptr<Course> course;

        if (type == "Lecture")
        {
            course =
                std::make_unique<LectureCourse>(
                    code,
                    title,
                    credit,
                    capacity,
                    *lecturer,
                    prerequisites
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
                    *lecturer,
                    prerequisites
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
                    *lecturer,
                    prerequisites
                );
        }
        else
        {
            throw CorruptDataException(
                "Unknown course type: " +
                type
            );
        }

        // -----------------------------
        // Load time slots
        //
        // Multiple slots are separated
        // using ;
        //
        // Example:
        // Monday,8,10,Hall A;
        // Wednesday,9,11,Lab 2
        // -----------------------------

        std::istringstream slotListStream(
            timeSlotText
        );

        std::string slotText;
        bool addedSlot = false;

        while (std::getline(
            slotListStream,
            slotText,
            ';'))
        {
            if (slotText.empty())
            {
                throw CorruptDataException(
                    "Invalid time slot list "
                    "for course: " +
                    code
                );
            }

            std::istringstream slotStream(
                slotText
            );

            std::string day;
            std::string startText;
            std::string endText;
            std::string location;

            if (!std::getline(
                    slotStream,
                    day,
                    ',') ||
                !std::getline(
                    slotStream,
                    startText,
                    ',') ||
                !std::getline(
                    slotStream,
                    endText,
                    ',') ||
                !std::getline(
                    slotStream,
                    location))
            {
                throw CorruptDataException(
                    "Invalid time slot for course " +
                    code +
                    ": " +
                    slotText
                );
            }

            if (day.empty() ||
                startText.empty() ||
                endText.empty() ||
                location.empty())
            {
                throw CorruptDataException(
                    "Incomplete time slot for course " +
                    code +
                    ": " +
                    slotText
                );
            }

            const int startTime =
                parseInt(
                    startText,
                    "start time",
                    row
                );

            const int endTime =
                parseInt(
                    endText,
                    "end time",
                    row
                );

            if (startTime < 0 ||
                startTime > 23 ||
                endTime < 1 ||
                endTime > 24 ||
                startTime >= endTime)
            {
                throw CorruptDataException(
                    "Invalid time range for course " +
                    code +
                    ": " +
                    slotText
                );
            }

            course->addTimeSlot(
                TimeSlot(
                    day,
                    startTime,
                    endTime,
                    location
                )
            );

            addedSlot = true;
        }

        if (!addedSlot)
        {
            throw CorruptDataException(
                "Course has no time slots: " +
                code
            );
        }

        // Lecturer keeps a non-owning reference.
        lecturer->addCourse(*course);

        // Menu owns the actual Course object.
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

void Menu::save() const
{
    Repository<std::string> enrolmentRepository(
        "data/enrolments.txt"
    );

    std::vector<std::string> savedRows;

    for (const auto& user : users)
    {
        const Student* student =
            dynamic_cast<const Student*>(user.get());

        if (student == nullptr)
        {
            continue;
        }

        for (const auto& enrolment : student->enrolments)
        {
            if (enrolment == nullptr ||
                enrolment->course == nullptr)
            {
                continue;
            }

            std::ostringstream row;

            row << student->getId()
                << "|"
                << enrolment->course->getCode()
                << "|"
                << enrolment->status
                << "|"
                << enrolment->dateEnrolled
                << "|"
                << enrolment->grade;

            savedRows.push_back(row.str());
        }
    }

    enrolmentRepository.save(savedRows);
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


