#ifndef ENROLMENT_H
#define ENROLMENT_H

#include <iostream>
#include <string>

using namespace std;

class Student;
class Course;
class AssessmentMarks;

class Enrolment
{
private:
    Student* student;
    Course* course;
    string status;
    string dateEnrolled;
    double grade;
    AssessmentMarks* assessmentMarks;

public:
    Enrolment(Student& student,
              Course& course,
              const string& status,
              const string& dateEnrolled,
              double grade);

    double getGrade() const;
    bool isCompleted() const;
    Student* getStudent() const;
    Course* getCourse() const;

    void setAssessmentMarks(AssessmentMarks& marks);
    void calculateGrade();

    friend ostream& operator<<(ostream& os,
                               const Enrolment& enrolment);
};

#endif