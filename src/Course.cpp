#include "Course.h"

Course::Course(const string& code, const string& title, int credit, int capacity,
               Lecturer& asignlecturer, const list<string>& prerequisites)
    : code(code),
      title(title),
      credit(credit),
      capacity(capacity),
      enroledstudentdetails(),
      prerequisites(prerequisites),
      asignlecturer(&asignlecturer),
      timeslot() {}

bool Course::isfull() const {
    return static_cast<int>(enroledstudentdetails.size()) >= capacity;
}

bool Course::hasPrerequistes(const string& code) const {
    for (const string& prerequisite : prerequisites) {
        if (prerequisite == code) {
            return true;
        }
    }
    return false;
}

list<Enrolment*> Course::viewenrolment() const {
    return enroledstudentdetails;
}

string Course::getcode() const {
    return code;
}

void Course::addTimeSlot(const TimeSlot& slot) {
    timeslot.push_back(slot);
}

list<TimeSlot> Course::getTimeSlots() const {
    return timeslot;
}

ostream& operator<<(ostream& os, const Course& c) {
    os << "Course [Code: " << c.code
       << ", Title: " << c.title
       << ", Credit: " << c.credit
       << ", Capacity: " << c.capacity
       << ", Enrolled: " << c.enroledstudentdetails.size()
       << "]";

    return os;
}