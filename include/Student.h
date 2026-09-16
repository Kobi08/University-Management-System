#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Person.h"
#include "Timetable.h"
#include "Course.h"

using namespace std;

class Student : public Person
{
private:
    Timetable timetable;

public:
    Student(const string& name, const string& password);

    void enrollcourse(Course& course);
    void dropcourse(Course& course);
    bool hascompleted(const string& courseCode) const;
    bool isenrolled(const Course& course) const;
    void viewtimetable() const;

    void showMenu() override;

    friend ostream& operator<<(ostream& os, const Student& student);
};

#endif
