#pragma once

#include <iostream>
#include <list>
#include <string>
#include "TimeSlot.h"
using namespace std;

class Enrolment;
class Lecturer;

class Course {
private:
    string code;
    string title;
    int credit;
    int capacity;

    list<Enrolment*> enrolledstudentdetails;

    list<string> prerequisites;

    Lecturer* assignedlecturer;

    list<TimeSlot> timeslots;

public:
    Course(const string& code, const string& title, int credit, int capacity,
           Lecturer& assignedlecturer,
           const list<string>& prerequisites = {});

    virtual ~Course() = default;

    virtual double calculateGrade() const = 0;

    bool isFull() const;
    bool hasPrerequisites(const string& code) const;
    list<Enrolment*> viewEnrolment() const;
    string getCode() const;

    void addTimeSlot(const TimeSlot& slot);
    list<TimeSlot> getTimeSlots() const;

    friend ostream& operator<<(ostream& os, const Course& c);
};