#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include <ctime>

#include "Course.h"
#include "TimeSlot.h"

using namespace std;

class AttendanceCapture;

class AttendanceSession
{
private:
    Course* course;
    TimeSlot timeslot;
    time_t opentime;
    bool isopen;
    int durationminute;
    AttendanceCapture* capture;

public:
    AttendanceSession();

    void open();
    void close();
    bool isExpired();

    void setcapturemethod(AttendanceCapture* c);

    AttendanceSession& operator=(const AttendanceSession&) = delete;

    AttendanceSession(AttendanceSession&& other);

    AttendanceSession& operator=(AttendanceSession&& other);

    ~AttendanceSession();
};

#endif