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

    AttendanceSession(Course& course,
                      const TimeSlot& timeslot,
                      int durationminute);

    void open();
    void close();
    bool isExpired();

    bool isOpen() const;

    Course* getCourse() const;
    const TimeSlot& getTimeSlot() const;

    int getDurationMinute() const;

    void setcapturemethod(AttendanceCapture* c);

    AttendanceSession& operator=(const AttendanceSession&) = delete;

    AttendanceSession(AttendanceSession&& other);

    AttendanceSession& operator=(AttendanceSession&& other);

    ~AttendanceSession();

    friend class AttendanceRegister;
};

#endif