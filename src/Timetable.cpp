#include "Timetable.h"

#include <iostream>

using namespace std;

void Timetable::addCourse(Course& course)
{
    courses.push_back(&course);
}

void Timetable::removeCourse(Course& course)
{
    courses.remove(&course);
}

bool Timetable::hasClash(const Course& course) const
{
    list<TimeSlot> newSlots = course.getTimeSlots();

    for (Course* existingCourse : courses)
    {
        list<TimeSlot> existingSlots = existingCourse->getTimeSlots();

        for (const TimeSlot& existing : existingSlots)
        {
            for (const TimeSlot& incoming : newSlots)
            {
                if (existing == incoming)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Timetable::display() const
{
    cout << "\n===== Timetable =====\n";

    for (Course* course : courses)
    {
        cout << *course << endl;

        for (const TimeSlot& slot : course->getTimeSlots())
        {
            cout << "   " << slot << endl;
        }
    }
}

list<Course*> Timetable::getCourses() const
{
    return courses;
}