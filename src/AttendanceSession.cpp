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

AttendanceSession::AttendanceSession(Course& course,
                                     const TimeSlot& timeslot,
                                     int durationminute)
{
    this->course = &course;
    this->timeslot = timeslot;
    this->opentime = 0;
    this->isopen = false;
    this->durationminute = durationminute;
    this->capture = nullptr;
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
bool AttendanceSession::isOpen() const
{
    return isopen;
}

Course* AttendanceSession::getCourse() const
{
    return course;
}

const TimeSlot& AttendanceSession::getTimeSlot() const
{
    return timeslot;
}

int AttendanceSession::getDurationMinute() const
{
    return durationminute;
}

void AttendanceSession::setcapturemethod(AttendanceCapture* c)
{
    capture = c;
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
{}