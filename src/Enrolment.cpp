#include "Enrolment.h"

#include "Student.h"
#include "Course.h"

#include <iostream>

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
      grade(grade)
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

ostream& operator<<(ostream& os,
                    const Enrolment& enrolment)
{
    os << "Enrolment [Student: "
       << enrolment.student->getName()
       << ", Course: "
       << enrolment.course->getcode()
       << ", Status: "
       << enrolment.status
       << ", Date Enrolled: "
       << enrolment.dateEnrolled
       << ", Grade: "
       << enrolment.grade
       << "]";

    return os;
}