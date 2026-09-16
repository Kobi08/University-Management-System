#ifndef ATTENDANCE_CAPTURE_H
#define ATTENDANCE_CAPTURE_H

#include <string>
using namespace std;

class AttendanceCapture
{
public:
    virtual ~AttendanceCapture() = default;

    virtual void beginSession() = 0;
    virtual void endSession() = 0;
    virtual string captureNext() = 0;
};

#endif