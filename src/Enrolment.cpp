#include "Enrolment.h"

#include "Student.h"
#include "Course.h"
#include "AssessmentMarks.h"

#include <iostream>
#include <stdexcept>

using namespace std;

Enrolment::Enrolment(Student& student,
                     Course& course,
                     const string& status,
                     const string& dateEnrolled,
                     double grade)
    : student(&student),
      course(&course),
      status(status),
      dateEnrolled(dateEnrolled),
      grade(grade),
      assessmentMarks(nullptr)
{
}

double Enrolment::getGrade() const
{
    return grade;
}

bool Enrolment::isCompleted() const
{
    return status == "Completed";
}
Student* Enrolment::getStudent() const
{
    return student;
}

Course* Enrolment::getCourse() const
{
    return course;
}

void Enrolment::setAssessmentMarks(AssessmentMarks& marks)
{
    assessmentMarks = &marks;
}

void Enrolment::calculateGrade()
{
    // TODO: Replace the temporary standard exception with
    // the final custom exception hierarchy once it is created.

    if (assessmentMarks == nullptr)
    {
        throw invalid_argument(
            "Assessment marks have not been assigned"
        );
    }

    grade = course->calculateGrade(*assessmentMarks);
}

ostream& operator<<(ostream& os,
                    const Enrolment& enrolment)
{
    os << "Enrolment [Student: "
       << enrolment.student->getName()
       << ", Course: "
       << enrolment.course->getCode()
       << ", Status: "
       << enrolment.status
       << ", Date Enrolled: "
       << enrolment.dateEnrolled
       << ", Grade: "
       << enrolment.grade
       << "]";

    return os;
}