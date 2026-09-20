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

    // Stores closed sessions so AttendanceRecord objects
    // can continue referring to valid AttendanceSession objects.
    list<AttendanceSession*> sessionHistory;

public:
    Lecturer(const string& name,
             const string& password);

        Lecturer(const Lecturer&) = delete;

    Lecturer& operator=(const Lecturer&) = delete;

    void showMenu() override;

    void viewEnrolment(Course& course) const;

    void addCourse(Course& course);

    void openAttendanceSession(const TimeSlot& slot,
                               int durationminute);

    void closeAttendanceSession();

    AttendanceSession* getActiveSession() const;

    ~Lecturer() override;

};

#endif