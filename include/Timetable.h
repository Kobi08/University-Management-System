#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <iostream>
#include <list>

#include "Course.h"

using namespace std;

class Timetable
{
private:
    list<Course*> courses;

public:
    void addCourse(Course& course);

    void removeCourse(Course& course);

    void display() const;

    bool hasClash(const Course& c) const;
};

#endif