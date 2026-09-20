#include "Student.h"
#include "Course.h"
#include "Exceptions.h"
#include "Enrolment.h"
#include "Menu.h"
#include <functional>
#include <set>

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

Student::~Student() = default;

void Student::showMenu()
{
    cout << "\n===== Student Menu (" << getName() << ") =====\n";
    cout << "1. Enroll in a course\n";
    cout << "2. Drop a course\n";
    cout << "3. View my timetable\n";
    cout << "4. Check course completion\n";
    cout << "0. Logout\n";

    // TODO: Menu choice handling will be connected by the Menu/UI layer.
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