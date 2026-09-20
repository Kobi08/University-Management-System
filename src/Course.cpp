#include "Course.h"
#include "Enrolment.h"

Course::Course(const string& code,
               const string& title,
               int credit,
               int capacity,
               Lecturer& asignlecturer,
               const list<string>& prerequisites)
    : code(code),
      title(title),
      credit(credit),
      capacity(capacity),
      enroledstudentdetails(),
      prerequisites(prerequisites),
      asignlecturer(&asignlecturer),
      timeslot()
{
}

bool Course::isFull() const
{
    int activeEnrolments = 0;

    for (const Enrolment* enrolment :
         enroledstudentdetails)
    {
        if (enrolment != nullptr &&
            !enrolment->isCompleted())
        {
            ++activeEnrolments;
        }
    }

    return activeEnrolments >= capacity;
}

bool Course::hasPrerequisites(const string& code) const
{
   

    for (const string& prerequisite : prerequisites)
    {
        if (prerequisite == code)
        {
            return true;
        }
    }

    return false;
}

list<Enrolment*> Course::viewEnrolment() const
{
    

    return enroledstudentdetails;
}

void Course::addEnrolment(Enrolment& enrolment)
{
    enroledstudentdetails.push_back(&enrolment);
}
void Course::removeEnrolment(Enrolment& enrolment)
{
    enroledstudentdetails.remove(&enrolment);
}

string Course::getCode() const
{
    return code;
}

Lecturer* Course::getLecturer() const
{
    return asignlecturer;
}

void Course::addTimeSlot(const TimeSlot& slot)
{
   

    timeslot.push_back(slot);
}

list<TimeSlot> Course::getTimeSlots() const
{
    

    return timeslot;
}

ostream& operator<<(ostream& os, const Course& c)
{
    os << "Course [Code: " << c.code
       << ", Title: " << c.title
       << ", Credit: " << c.credit
       << ", Capacity: " << c.capacity
       << ", Enrolled: " << c.enroledstudentdetails.size()
       << "]";

    return os;
}