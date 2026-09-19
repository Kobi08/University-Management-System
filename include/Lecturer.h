#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <string>
#include <list>

#include "Person.h"

using namespace std;

class Course;
class TimeSlot;
class AttendanceSession;

class Lecturer : public Person
{
private:
    list<Course*> assignedCourse;
    AttendanceSession* activeSession;

public:
    Lecturer(const string& name,
             const string& password);

    void showMenu() override;

    void viewEnrolment(Course& course) const;

    // TODO: Connect to Member 2's TimeSlot and AttendanceSession
    // implementation when those classes are available.
    void addCourse(Course& course);
    void openAttendanceSession(const TimeSlot& slot, int durationminute);
    // TODO: Connect to Member 2's AttendanceSession implementation.
    void closeAttendanceSession();
    AttendanceSession* getActiveSession() const;

    ~Lecturer() override = default;
};

#endif