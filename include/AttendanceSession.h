#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include <ctime>
#include <string>
#include <vector>

#include "Course.h"
#include "TimeSlot.h"

class AttendanceCapture;
class AttendanceRegister;
class Menu;

class AttendanceSession
{
private:
    friend class AttendanceRegister;
    friend class Menu;

    Course* course;
    TimeSlot timeslot;

    std::time_t opentime;
    bool isopen;
    int durationminute;

    // Owned by this session.
    AttendanceCapture* capture;

    // Students eligible when the session opened.
    std::vector<std::string> eligibleStudentIds;

public:
    AttendanceSession();

    AttendanceSession(
        Course& course,
        const TimeSlot& timeslot,
        int durationminute
    );

    void open();
    void close();

    bool isExpired();
    bool isOpen() const;

    Course* getCourse() const;
    const TimeSlot& getTimeSlot() const;

    void setcapturemethod(AttendanceCapture* c);

    std::string captureNext();
    std::string captureName() const;

    const std::vector<std::string>& eligibleStudents() const;

    AttendanceSession(const AttendanceSession&) = delete;

    AttendanceSession& operator=(
        const AttendanceSession&
    ) = delete;

    AttendanceSession(AttendanceSession&& other);

    AttendanceSession& operator=(
        AttendanceSession&& other
    );

    ~AttendanceSession();
};

#endif