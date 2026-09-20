#pragma once

#include <iostream>
#include <list>
#include <string>

#include "TimeSlot.h"

using namespace std;

class Course;
class Enrolment;
class Lecturer;
class AssessmentMarks;
class Menu;
class Administrator;

class Course
{
private:
    string code;
    string title;
    int credit;
    int capacity;
    friend class Menu;
    friend class Administrator;

    list<Enrolment*> enroledstudentdetails;
    list<string> prerequisites;
    Lecturer* asignlecturer;
    list<TimeSlot> timeslot;

public:
    Course(const string& code,
           const string& title,
           int credit,
           int capacity,
           Lecturer& asignlecturer,
           const list<string>& prerequisites = {});
    
    const list<string>& getPrerequisites() const
    {
        return prerequisites;
    }
    virtual ~Course() = default;

    virtual double calculateGrade(const AssessmentMarks& marks) const = 0;
    virtual string getCourseType() const = 0;

    bool isFull() const;

    bool hasPrerequisites(const string& code) const;

    list<Enrolment*> viewEnrolment() const;


   void addEnrolment(Enrolment& enrolment);
   void removeEnrolment(Enrolment& enrolment);
    string getCode() const;

    Lecturer* getLecturer() const;

    void addTimeSlot(const TimeSlot& slot);

    list<TimeSlot> getTimeSlots() const;

    friend ostream& operator<<(ostream& os, const Course& c);
};