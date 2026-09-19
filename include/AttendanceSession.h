#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include <ctime>

#include "Course.h"
#include "TimeSlot.h"

using namespace std;

class AttendanceCapture;
class AttendanceRegister;

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

    void setcourse(Course* course);
    void settimeslot(const TimeSlot& timeslot);
    void setduration(int durationminute);

    bool isopenstatus() const;

    Course* getcourse() const;
    const TimeSlot& gettimeslot() const;

    AttendanceSession& operator=(const AttendanceSession&) = delete;

    AttendanceSession(AttendanceSession&& other);

    AttendanceSession& operator=(AttendanceSession&& other);

    ~AttendanceSession();

    friend class AttendanceRegister;
};

#endif