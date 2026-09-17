#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Person.h"
#include "Timetable.h"

using namespace std;

class Course;

class Student : public Person
{
private:
    Timetable timetable;

public:
    Student(const string& name, const string& password);

    Student(const string& name,
        const string& password,
        const string& id);

    void showMenu() override;

    void enrollCourse(Course& course);
    void dropCourse(Course& course);

    bool hasCompleted(const string& courseCode) const;
    bool isEnrolled(const Course& course) const;

    void viewTimetable() const;

    friend ostream& operator<<(ostream& os, const Student& s);

    ~Student() override = default;
};

#endif