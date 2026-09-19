#include "Timetable.h"

using namespace std;

void Timetable::addCourse(Course& course)
{
    courses.push_back(&course);
}

void Timetable::removeCourse(Course& course)
{
    courses.remove(&course);
}

void Timetable::display() const
{
    for (Course* course : courses)
    {
        if (course != nullptr)
        {
            cout << *course << endl;
        }
    }
}

bool Timetable::hasClash(const Course& c) const
{
    list<TimeSlot> newCourseSlots = c.getTimeSlots();

    for (Course* existingCourse : courses)
    {
        if (existingCourse == nullptr)
        {
            continue;
        }

        list<TimeSlot> existingCourseSlots =
            existingCourse->getTimeSlots();

        for (const TimeSlot& existingSlot : existingCourseSlots)
        {
            for (const TimeSlot& newSlot : newCourseSlots)
            {
                if (existingSlot == newSlot)
                {
                    return true;
                }
            }
        }
    }

    return false;
}