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
#include <filesystem>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Repository.h"
#include <unordered_set>
#include <algorithm>

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
    loadAttendance();


        while (!stop)
        {
            showloginmenu();

            std::string id = ask("User ID: ");

           if (id == "0")
{
    save();

    stop = true;

    std::cout
        << "Application closed.\n";

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
{   Repository<std::string>
    attendanceSessionRepository(
        "data/attendance_sessions.txt"
    );

Repository<std::string>
    attendanceRecordRepository(
        "data/attendance_records.txt"
    );

Repository<std::string>
    attendanceCorrectionRepository(
        "data/attendance_corrections.txt"
    );
    Repository<std::string> studentRepository(
        "data/students.txt"
    );

    Repository<std::string> lecturerRepository(
        "data/lecturers.txt"
    );

    Repository<std::string> administratorRepository(
        "data/administrators.txt"
    );

    Repository<std::string> courseRepository(
        "data/courses.txt"
    );

    Repository<std::string> enrolmentRepository(
        "data/enrolments.txt"
    );

    std::vector<std::string> studentRows;
    std::vector<std::string> lecturerRows;
    std::vector<std::string> administratorRows;
    std::vector<std::string> courseRows;
    std::vector<std::string> enrolmentRows;
    std::vector<std::string>
    attendanceSessionRows;

std::vector<std::string>
    attendanceRecordRows;

std::vector<std::string>
    attendanceCorrectionRows;
    // =====================================================
    // USERS
    // =====================================================

    for (const auto& user : users)
    {
        if (user == nullptr)
        {
            continue;
        }

        std::ostringstream row;

        row << user->getId()
            << "|"
            << user->getName()
            << "|"
            << user->password;

        if (dynamic_cast<const Student*>(user.get()) != nullptr)
        {
            studentRows.push_back(row.str());
        }
        else if (dynamic_cast<const Lecturer*>(user.get()) != nullptr)
        {
            lecturerRows.push_back(row.str());
        }
        else if (dynamic_cast<const Administrator*>(user.get()) != nullptr)
        {
            administratorRows.push_back(row.str());
        }
        else
        {
            throw PersistenceException(
                "Unknown user type while saving."
            );
        }
    }

    // =====================================================
    // COURSES
    // =====================================================

    for (const auto& course : courses)
    {
        if (course == nullptr)
        {
            continue;
        }

        if (course->asignlecturer == nullptr)
        {
            throw PersistenceException(
                "Course " +
                course->code +
                " has no assigned lecturer."
            );
        }

        std::ostringstream prerequisiteText;

        if (course->prerequisites.empty())
        {
            prerequisiteText << "-";
        }
        else
        {
            bool first = true;

            for (const std::string& prerequisite :
                 course->prerequisites)
            {
                if (!first)
                {
                    prerequisiteText << ",";
                }

                prerequisiteText << prerequisite;
                first = false;
            }
        }

        if (course->timeslot.empty())
        {
            throw PersistenceException(
                "Course " +
                course->code +
                " has no time slot."
            );
        }

        std::ostringstream timeSlotText;

        bool firstSlot = true;

        for (const TimeSlot& slot :
             course->timeslot)
        {
            if (!firstSlot)
            {
                timeSlotText << ";";
            }

            timeSlotText
                << slot.getDay()
                << ","
                << slot.getStartTime()
                << ","
                << slot.getEndTime()
                << ","
                << slot.getLocation();

            firstSlot = false;
        }

        std::ostringstream row;

        row << course->getCourseType()
            << "|"
            << course->code
            << "|"
            << course->title
            << "|"
            << course->credit
            << "|"
            << course->capacity
            << "|"
            << course->asignlecturer->getId()
            << "|"
            << prerequisiteText.str()
            << "|"
            << timeSlotText.str();

        courseRows.push_back(
            row.str()
        );
    }

    // =====================================================
    // ENROLMENTS
    // =====================================================

    for (const auto& user : users)
    {
        const Student* student =
            dynamic_cast<const Student*>(
                user.get()
            );

        if (student == nullptr)
        {
            continue;
        }

        for (const auto& enrolment :
             student->enrolments)
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

            enrolmentRows.push_back(
                row.str()
            );
        }
    }

    // =====================================================
// ATTENDANCE SESSIONS
// =====================================================

std::unordered_map<
    const AttendanceSession*,
    std::string
> sessionIds;

int sessionNumber = 1;

for (AttendanceSession* session :
     attendance.sessions)
{
    if (session == nullptr ||
        session->course == nullptr)
    {
        continue;
    }

    const std::string sessionId =
        "S" +
        std::to_string(
            sessionNumber++
        );

    sessionIds[
        session
    ] = sessionId;

    std::ostringstream eligible;

    if (session->
            eligibleStudentIds
            .empty())
    {
        eligible << "-";
    }
    else
    {
        bool first = true;

        for (const std::string& studentId :
             session->
                 eligibleStudentIds)
        {
            if (!first)
            {
                eligible << ",";
            }

            eligible << studentId;
            first = false;
        }
    }

    const TimeSlot& slot =
        session->timeslot;

    std::ostringstream row;

    row << sessionId
        << "|"
        << session->course->getCode()
        << "|"
        << slot.getDay()
        << "|"
        << slot.getStartTime()
        << "|"
        << slot.getEndTime()
        << "|"
        << slot.getLocation()
        << "|"
        << static_cast<long long>(
            session->opentime
        )
        << "|"
        << session->durationminute
        << "|"
        << eligible.str();

    attendanceSessionRows.push_back(
        row.str()
    );
}

// =====================================================
// ATTENDANCE RECORDS
// =====================================================

for (const AttendanceRecord& record :
     attendance.records)
{
    if (record.student == nullptr ||
        record.session == nullptr)
    {
        continue;
    }

    auto sessionIt =
        sessionIds.find(
            record.session
        );

    if (sessionIt ==
        sessionIds.end())
    {
        throw PersistenceException(
            "Attendance record refers to "
            "an unknown attendance session."
        );
    }

    std::ostringstream row;

    row << record.student->getId()
        << "|"
        << sessionIt->second
        << "|"
        << record.status
        << "|"
        << static_cast<long long>(
            record.timestamp
        )
        << "|"
        << record.capturedby;

    attendanceRecordRows.push_back(
        row.str()
    );
}

// =====================================================
// ATTENDANCE CORRECTIONS
// =====================================================

for (const CorrectionRecord& correction :
     attendance.corrections)
{
    const AttendanceRecord& original =
        correction.originalrecord;

    if (original.student == nullptr ||
        original.session == nullptr ||
        correction.actinglecuturer ==
            nullptr)
    {
        continue;
    }

    auto sessionIt =
        sessionIds.find(
            original.session
        );

    if (sessionIt ==
        sessionIds.end())
    {
        throw PersistenceException(
            "Attendance correction refers "
            "to an unknown session."
        );
    }

    std::string safeReason =
        correction.reason;

    // Our text format uses | as its delimiter.
    // Avoid corrupting the row if a lecturer
    // types a pipe in the correction reason.
    std::replace(
        safeReason.begin(),
        safeReason.end(),
        '|',
        '/'
    );

    std::ostringstream row;

    row << original.student->getId()
        << "|"
        << sessionIt->second
        << "|"
        << correction.actinglecuturer
               ->getId()
        << "|"
        << correction.correctedStatus
        << "|"
        << safeReason
        << "|"
        << static_cast<long long>(
            correction.timestamp
        );

    attendanceCorrectionRows.push_back(
        row.str()
    );
}

    studentRepository.save(
        studentRows
    );

    lecturerRepository.save(
        lecturerRows
    );

    administratorRepository.save(
        administratorRows
    );

    courseRepository.save(
        courseRows
    );

    enrolmentRepository.save(
        enrolmentRows
    );

    attendanceSessionRepository.save(
    attendanceSessionRows
);

attendanceRecordRepository.save(
    attendanceRecordRows
);

attendanceCorrectionRepository.save(
    attendanceCorrectionRows
);
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

bool Menu::userReferenced(
    const Person* user) const
{
    if (user == nullptr)
    {
        return false;
    }

    // A lecturer cannot be removed while
    // a course still refers to them.
    for (const auto& course :
         courses)
    {
        if (course != nullptr &&
            course->getLecturer() == user)
        {
            return true;
        }
    }

    // Preserve student enrolment history.
    const Student* student =
        dynamic_cast<const Student*>(
            user
        );

    if (student != nullptr &&
        !student->enrolments.empty())
    {
        return true;
    }

    return false;
}

bool Menu::courseReferenced(
    const Course* course) const
{
    if (course == nullptr)
    {
        return false;
    }

    // Check student enrolment history.
    for (const auto& user : users)
    {
        const Student* student =
            dynamic_cast<const Student*>(
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
                enrolment->getCourse() == course)
            {
                return true;
            }
        }
    }

    // Also protect courses that are prerequisites
    // of another course.
    for (const auto& otherCourse :
         courses)
    {
        if (otherCourse == nullptr ||
            otherCourse.get() == course)
        {
            continue;
        }

        for (const std::string& prerequisite :
             otherCourse->getPrerequisites())
        {
            if (prerequisite ==
                course->getCode())
            {
                return true;
            }
        }
    }

    return false;
}

void Menu::loadAttendance()
{
    namespace fs = std::filesystem;

    attendance.records.clear();
    attendance.corrections.clear();
    attendance.sessions.clear();

    const std::string sessionPath =
        "data/attendance_sessions.txt";

    const std::string recordPath =
        "data/attendance_records.txt";

    const std::string correctionPath =
        "data/attendance_corrections.txt";

    // First run: attendance files may not exist yet.
    // Treat them as empty attendance history.
    if (!fs::exists(sessionPath))
    {
        return;
    }

    Repository<std::string> sessionRepository(
        sessionPath
    );

    std::unordered_map<
        std::string,
        AttendanceSession*
    > sessionMap;

    // =================================================
    // LOAD SESSIONS
    // =================================================

    for (const std::string& row :
         sessionRepository.load())
    {
        std::istringstream input(row);

        std::string sessionId;
        std::string courseCode;
        std::string day;
        std::string startText;
        std::string endText;
        std::string location;
        std::string openTimeText;
        std::string durationText;
        std::string eligibleText;

        if (!std::getline(input, sessionId, '|') ||
            !std::getline(input, courseCode, '|') ||
            !std::getline(input, day, '|') ||
            !std::getline(input, startText, '|') ||
            !std::getline(input, endText, '|') ||
            !std::getline(input, location, '|') ||
            !std::getline(input, openTimeText, '|') ||
            !std::getline(input, durationText, '|') ||
            !std::getline(input, eligibleText))
        {
            throw CorruptDataException(
                "Invalid attendance session record: " +
                row
            );
        }

        if (sessionMap.find(sessionId)
            != sessionMap.end())
        {
            throw CorruptDataException(
                "Duplicate attendance session ID: " +
                sessionId
            );
        }

        Course* course =
            findCourse(courseCode);

        if (course == nullptr)
        {
            throw CorruptDataException(
                "Attendance session references "
                "unknown course: " +
                courseCode
            );
        }

        Lecturer* lecturer =
            course->getLecturer();

        if (lecturer == nullptr)
        {
            throw CorruptDataException(
                "Attendance session course has "
                "no lecturer: " +
                courseCode
            );
        }

        int startTime;
        int endTime;
        int duration;
        std::time_t openTime;

        try
        {
            startTime =
                std::stoi(startText);

            endTime =
                std::stoi(endText);

            duration =
                std::stoi(durationText);

            openTime =
                static_cast<std::time_t>(
                    std::stoll(openTimeText)
                );
        }
        catch (...)
        {
            throw CorruptDataException(
                "Invalid number in attendance "
                "session record: " +
                row
            );
        }

        if (duration <= 0 ||
            startTime < 0 ||
            endTime > 24 ||
            startTime >= endTime)
        {
            throw CorruptDataException(
                "Invalid attendance session values: " +
                row
            );
        }

        TimeSlot slot(
            day,
            startTime,
            endTime,
            location
        );

        AttendanceSession* session =
            new AttendanceSession(
                *course,
                slot,
                duration
            );

        // Menu is a friend of AttendanceSession.
        // Restored sessions are historical/closed.
        session->opentime =
            openTime;

        session->isopen =
            false;

        session->eligibleStudentIds.clear();

        if (eligibleText != "-" &&
            !eligibleText.empty())
        {
            std::istringstream eligibleStream(
                eligibleText
            );

            std::string studentId;

            while (std::getline(
                eligibleStream,
                studentId,
                ','))
            {
                if (!studentId.empty())
                {
                    session->
                        eligibleStudentIds
                        .push_back(
                            studentId
                        );
                }
            }
        }

        // Lecturer owns historical sessions.
        lecturer->sessionHistory.push_back(
            session
        );

        // AttendanceRegister keeps a non-owning reference.
        attendance.registerSession(
            *session
        );

        sessionMap[
            sessionId
        ] = session;
    }

    // =================================================
    // LOAD ATTENDANCE RECORDS
    // =================================================

    if (fs::exists(recordPath))
    {
        Repository<std::string> recordRepository(
            recordPath
        );

        for (const std::string& row :
             recordRepository.load())
        {
            std::istringstream input(row);

            std::string studentId;
            std::string sessionId;
            std::string status;
            std::string timestampText;
            std::string capturedBy;

            if (!std::getline(
                    input,
                    studentId,
                    '|') ||
                !std::getline(
                    input,
                    sessionId,
                    '|') ||
                !std::getline(
                    input,
                    status,
                    '|') ||
                !std::getline(
                    input,
                    timestampText,
                    '|') ||
                !std::getline(
                    input,
                    capturedBy))
            {
                throw CorruptDataException(
                    "Invalid attendance record: " +
                    row
                );
            }

            Student* student =
                dynamic_cast<Student*>(
                    findUser(studentId)
                );

            if (student == nullptr)
            {
                throw CorruptDataException(
                    "Attendance record references "
                    "unknown student: " +
                    studentId
                );
            }

            auto sessionIt =
                sessionMap.find(
                    sessionId
                );

            if (sessionIt ==
                sessionMap.end())
            {
                throw CorruptDataException(
                    "Attendance record references "
                    "unknown session: " +
                    sessionId
                );
            }

            std::time_t timestamp;

            try
            {
                timestamp =
                    static_cast<std::time_t>(
                        std::stoll(
                            timestampText
                        )
                    );
            }
            catch (...)
            {
                throw CorruptDataException(
                    "Invalid attendance timestamp: " +
                    row
                );
            }

            attendance.records.emplace_back(
                student,
                sessionIt->second,
                status,
                timestamp,
                capturedBy
            );
        }
    }

    // =================================================
    // LOAD CORRECTIONS
    // =================================================

    if (fs::exists(correctionPath))
    {
        Repository<std::string>
            correctionRepository(
                correctionPath
            );

        for (const std::string& row :
             correctionRepository.load())
        {
            std::istringstream input(row);

            std::string studentId;
            std::string sessionId;
            std::string lecturerId;
            std::string correctedStatus;
            std::string reason;
            std::string timestampText;

            if (!std::getline(
                    input,
                    studentId,
                    '|') ||
                !std::getline(
                    input,
                    sessionId,
                    '|') ||
                !std::getline(
                    input,
                    lecturerId,
                    '|') ||
                !std::getline(
                    input,
                    correctedStatus,
                    '|') ||
                !std::getline(
                    input,
                    reason,
                    '|') ||
                !std::getline(
                    input,
                    timestampText))
            {
                throw CorruptDataException(
                    "Invalid attendance correction: " +
                    row
                );
            }

            Student* student =
                dynamic_cast<Student*>(
                    findUser(studentId)
                );

            Lecturer* lecturer =
                dynamic_cast<Lecturer*>(
                    findUser(lecturerId)
                );

            if (student == nullptr)
            {
                throw CorruptDataException(
                    "Correction references unknown "
                    "student: " +
                    studentId
                );
            }

            if (lecturer == nullptr)
            {
                throw CorruptDataException(
                    "Correction references unknown "
                    "lecturer: " +
                    lecturerId
                );
            }

            auto sessionIt =
                sessionMap.find(
                    sessionId
                );

            if (sessionIt ==
                sessionMap.end())
            {
                throw CorruptDataException(
                    "Correction references unknown "
                    "session: " +
                    sessionId
                );
            }

            AttendanceRecord* original =
                nullptr;

            for (AttendanceRecord& record :
                 attendance.records)
            {
                if (record.student ==
                        student &&
                    record.session ==
                        sessionIt->second)
                {
                    original =
                        &record;

                    break;
                }
            }

            if (original == nullptr)
            {
                throw CorruptDataException(
                    "Correction has no matching "
                    "attendance record."
                );
            }

            std::time_t timestamp;

            try
            {
                timestamp =
                    static_cast<std::time_t>(
                        std::stoll(
                            timestampText
                        )
                    );
            }
            catch (...)
            {
                throw CorruptDataException(
                    "Invalid correction timestamp: " +
                    row
                );
            }

            attendance.corrections.emplace_back(
                *original,
                *lecturer,
                reason,
                timestamp,
                correctedStatus
            );
        }
    }
}