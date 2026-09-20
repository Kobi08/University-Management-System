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
    os << enrolment.student->getId() << "|"
       << enrolment.course->getcode() << "|"
       << enrolment.status << "|"
       << enrolment.dateEnrolled << "|"
       << enrolment.grade;

    return os;
}