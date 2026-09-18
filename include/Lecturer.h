#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <string>
#include <list>

#include "Person.h"

using namespace std;

class Course;
class TimeSlot;

class Lecturer : public Person
{
private:
    list<Course*> assignedCourse;

public:
    Lecturer(const string& name,
             const string& password);

    void showMenu() override;

    void viewEnrolment(Course& course) const;

    // TODO: Connect to Member 2's TimeSlot and AttendanceSession
    // implementation when those classes are available.
    void openAttendanceSession(const TimeSlot& slot);

    // TODO: Connect to Member 2's AttendanceSession implementation.
    void closeAttendanceSession();

    ~Lecturer() override = default;
};

#endif