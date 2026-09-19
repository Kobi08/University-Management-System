#include "TimeSlot.h"

using namespace std;

TimeSlot::TimeSlot()
{
    day = "";
    startTime = 0;
    endTime = 0;
    location = "";
}

TimeSlot::TimeSlot(const string& day,
                   int startTime,
                   int endTime,
                   const string& location)
{
    this->day = day;
    this->startTime = startTime;
    this->endTime = endTime;
    this->location = location;
}

string TimeSlot::getDay() const
{
    return day;
}

int TimeSlot::getStartTime() const
{
    return startTime;
}

int TimeSlot::getEndTime() const
{
    return endTime;
}

string TimeSlot::getLocation() const
{
    return location;
}

bool TimeSlot::operator==(const TimeSlot& other) const
{
    if (day != other.day)
    {
        return false;
    }

    return startTime < other.endTime &&
           endTime > other.startTime;
}

ostream& operator<<(ostream& os, const TimeSlot& slot)
{
    os << slot.day
       << " "
       << slot.startTime
       << ":00-"
       << slot.endTime
       << ":00 at "
       << slot.location;

    return os;
}