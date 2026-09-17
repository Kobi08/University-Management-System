#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include <ctime>

#include "TimeSlot.h"

class Course;
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
    AttendanceSession(Course& course,
                      const TimeSlot& timeslot,
                      int durationminute);

    void open();
    void close();

    bool isExpired() const;

    void setCaptureMethod(AttendanceCapture* c);

    AttendanceSession& operator=(const AttendanceSession&) = delete;

    AttendanceSession(AttendanceSession&& other) noexcept;

    AttendanceSession& operator=(AttendanceSession&& other) noexcept;

    friend class AttendanceRegister;

    ~AttendanceSession();
};

#endif