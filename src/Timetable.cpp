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
    if (courses.empty())
    {
        cout << "No courses in timetable.\n";
        return;
    }

    cout << "\n===== WEEKLY TIMETABLE =====\n";

    for (Course* course : courses)
    {
        if (course == nullptr)
        {
            continue;
        }

        cout << "\n"
             << course->getCode()
             << "\n";

        const list<TimeSlot> slots =
            course->getTimeSlots();

        if (slots.empty())
        {
            cout << "  No time slots assigned.\n";
            continue;
        }

        for (const TimeSlot& slot : slots)
        {
            cout << "  " << slot << '\n';
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