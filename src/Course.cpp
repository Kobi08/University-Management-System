#include "Course.h"

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
    // TODO: Final enrolment count will be connected
    // with the final Enrolment implementation.

    return static_cast<int>(enroledstudentdetails.size()) >= capacity;
}

bool Course::hasPrerequisites(const string& code) const
{
    // TODO: This currently checks direct prerequisites only.
    // Recursive prerequisite-chain validation will be completed
    // as part of the Member 1 enrolment rules.

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
    // TODO: Display and management of enrolment information
    // will be connected to the final Enrolment implementation.

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
    // TODO: Connect with Member 2's final TimeSlot implementation
    // when the scheduling classes are available.

    timeslot.push_back(slot);
}

list<TimeSlot> Course::getTimeSlots() const
{
    // TODO: Connect with Member 2's final scheduling implementation
    // when the TimeSlot class is available.

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