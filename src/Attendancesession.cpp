#include "AttendanceSession.h"

#include "Course.h"

#include <ctime>
#include <utility>

AttendanceSession::AttendanceSession(Course& course,
                                     const TimeSlot& timeslot,
                                     int durationminute)
    : course(&course),
      timeslot(timeslot),
      opentime(0),
      isopen(false),
      durationminute(durationminute),
      capture(nullptr)
{
}

void AttendanceSession::open()
{
    isopen = true;
    opentime = std::time(nullptr);
}

void AttendanceSession::close()
{
    isopen = false;
}

bool AttendanceSession::isExpired() const
{
    if (!isopen)
    {
        return true;
    }

    time_t now = std::time(nullptr);

    return (now - opentime) >= durationminute * 60;
}

void AttendanceSession::setCaptureMethod(AttendanceCapture* c)
{
    capture = c;
}

AttendanceSession::AttendanceSession(AttendanceSession&& other) noexcept
    : course(other.course),
      timeslot(std::move(other.timeslot)),
      opentime(other.opentime),
      isopen(other.isopen),
      durationminute(other.durationminute),
      capture(other.capture)
{
    other.course = nullptr;
    other.capture = nullptr;
    other.isopen = false;
}

AttendanceSession& AttendanceSession::operator=(AttendanceSession&& other) noexcept
{
    if (this != &other)
    {
        course = other.course;
        timeslot = std::move(other.timeslot);
        opentime = other.opentime;
        isopen = other.isopen;
        durationminute = other.durationminute;
        capture = other.capture;

        other.course = nullptr;
        other.capture = nullptr;
        other.isopen = false;
    }

    return *this;
}

AttendanceSession::~AttendanceSession()
{
}