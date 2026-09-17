#ifndef ATTENDANCECAPTURE_H
#define ATTENDANCECAPTURE_H

#include <string>

class AttendanceCapture
{
public:
    virtual void beginSession() = 0;

    virtual std::string captureNext() = 0;

    virtual void endSession() = 0;

    virtual ~AttendanceCapture() = default;
};

#endif

//Every function is pure virtual and the destructor is defaulted so there is no need for .cpp file since there is nothing to implement.
