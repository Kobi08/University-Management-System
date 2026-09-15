#include "Course.h"

Course::Course(const string& code, const string& title, int credit, int capacity,
               Lecturer& assignedlecturer, const list<string>& prerequisites)
    : code(code),
      title(title),
      credit(credit),
      capacity(capacity),
      enrolledstudentdetails(),
      prerequisites(prerequisites),
      assignedlecturer(&assignedlecturer),
      timeslots() {}

bool Course::isFull() const {
    return static_cast<int>(enrolledstudentdetails.size()) >= capacity;
}

bool Course::hasPrerequisites(const string& code) const {
    for (const string& prerequisite : prerequisites) {
        if (prerequisite == code) {
            return true;
        }
    }
    return false;
}

list<Enrolment*> Course::viewEnrolment() const {
    return enrolledstudentdetails;
}

string Course::getCode() const {
    return code;
}

void Course::addTimeSlot(const TimeSlot& slot) {
    timeslots.push_back(slot);
}

list<TimeSlot> Course::getTimeSlots() const {
    return timeslots;
}

ostream& operator<<(ostream& os, const Course& c) {
    os << "Course [Code: " << c.code
       << ", Title: " << c.title
       << ", Credit: " << c.credit
       << ", Capacity: " << c.capacity
       << ", Enrolled: " << c.enrolledstudentdetails.size()
       << "]";

    return os;
}