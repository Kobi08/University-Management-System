#ifndef ENROLMENT_H
#define ENROLMENT_H

#include <iostream>
#include <string>

using namespace std;

class Student;
class Course;

class Enrolment
{
private:
    Student* student;
    Course* course;
    string status;
    string dateEnrolled;
    double grade;

public:
    Enrolment(Student& student,
              Course& course,
              const string& status,
              const string& dateEnrolled,
              double grade);

    double getGrade() const;

    bool isCompleted() const;

    friend ostream& operator<<(ostream& os,
                               const Enrolment& enrolment);

    template<typename T>
    friend class Repository;    
};

#endif