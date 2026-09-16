#pragma once

#include <iostream>
#include <list>
#include <string>
#include "TimeSlot.h"
using namespace std;

class Enrolment;
class Lecturer;
class AssessmentMarks;

class Course {
private:
    string code;
    string title;
    int credit;
    int capacity;

    list<Enrolment*> enroledstudentdetails;

    list<string> prerequisites;

    Lecturer* asignlecturer;

    list<TimeSlot> timeslot;

public:
    Course(const string& code, const string& title, int credit, int capacity,
           Lecturer& asignlecturer,
           const list<string>& prerequisites = {});

    virtual ~Course() = default;

    virtual double calculategrade(const AssessmentMarks& marks) const = 0;

    bool isfull() const;
    bool hasPrerequistes(const string& code) const;
    list<Enrolment*> viewenrolment() const;
    string getcode() const;

    void addTimeSlot(const TimeSlot& slot);
    list<TimeSlot> getTimeSlots() const;

    friend ostream& operator<<(ostream& os, const Course& c);
};