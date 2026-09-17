#ifndef ROTATINGCODECAPTURE_H
#define ROTATINGCODECAPTURE_H

#include <string>

#include "AttendanceCapture.h"

using namespace std;

class RotatingCodeCapture : public AttendanceCapture
{
private:
    string currentCode;

public:
    RotatingCodeCapture();

    void beginSession() override;
    string captureNext() override;
    void endSession() override;

    ~RotatingCodeCapture() override = default;
};

#endif