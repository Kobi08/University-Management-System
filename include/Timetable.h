#ifndef TIMETABLE_H
#define TIMETABLE_H

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

    bool hasClash(const Course& course) const;

    void display() const;

    list<Course*> getCourses() const;
};

#endif