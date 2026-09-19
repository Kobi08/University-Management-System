#include "AttendanceSession.h"
#include "AttendanceCapture.h"

using namespace std;

AttendanceSession::AttendanceSession()
{
    course = nullptr;
    timeslot = TimeSlot();
    opentime = 0;
    isopen = false;
    durationminute = 0;
    capture = nullptr;
}

void AttendanceSession::open()
{
    if (isopen)
    {
        return;
    }

    opentime = time(nullptr);
    isopen = true;

    if (capture != nullptr)
    {
        capture->beginSession();
    }
}

void AttendanceSession::close()
{
    if (!isopen)
    {
        return;
    }

    if (capture != nullptr)
    {
        capture->endSession();
    }

    isopen = false;
}

bool AttendanceSession::isExpired()
{
    if (!isopen)
    {
        return false;
    }

    if (durationminute <= 0)
    {
        return false;
    }

    time_t currentTime = time(nullptr);

    return difftime(currentTime, opentime)
           >= durationminute * 60;
}

void AttendanceSession::setcapturemethod(AttendanceCapture* c)
{
    capture = c;
}

void AttendanceSession::setcourse(Course* course)
{
    this->course = course;
}

void AttendanceSession::settimeslot(const TimeSlot& timeslot)
{
    this->timeslot = timeslot;
}

void AttendanceSession::setduration(int durationminute)
{
    this->durationminute = durationminute;
}

bool AttendanceSession::isopenstatus() const
{
    return isopen;
}

Course* AttendanceSession::getcourse() const
{
    return course;
}

const TimeSlot& AttendanceSession::gettimeslot() const
{
    return timeslot;
}

AttendanceSession::AttendanceSession(AttendanceSession&& other)
{
    course = other.course;
    timeslot = other.timeslot;
    opentime = other.opentime;
    isopen = other.isopen;
    durationminute = other.durationminute;
    capture = other.capture;

    other.course = nullptr;
    other.opentime = 0;
    other.isopen = false;
    other.durationminute = 0;
    other.capture = nullptr;
}

AttendanceSession& AttendanceSession::operator=(AttendanceSession&& other)
{
    if (this != &other)
    {
        course = other.course;
        timeslot = other.timeslot;
        opentime = other.opentime;
        isopen = other.isopen;
        durationminute = other.durationminute;
        capture = other.capture;

        other.course = nullptr;
        other.opentime = 0;
        other.isopen = false;
        other.durationminute = 0;
        other.capture = nullptr;
    }

    return *this;
}

AttendanceSession::~AttendanceSession()
{
}