#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

#include "Person.h"

using namespace std;

class Course;
class Timetable;

class Student : public Person
{
private:
    // TODO: Connect this pointer to Member 2's final Timetable implementation.
    Timetable* timetable;

public:
    Student(const string& name,
            const string& password);

    void showMenu() override;

    void enrollCourse(Course& course);
    void dropCourse(Course& course);

    bool hasCompleted(const string& courseCode) const;
    bool isEnrolled(const Course& course) const;

    void viewTimetable() const;

    friend ostream& operator<<(ostream& os, const Student& student);

    ~Student() override = default;
};

#endif