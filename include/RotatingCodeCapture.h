#ifndef ROTATINGCODECAPTURE_H
#define ROTATINGCODECAPTURE_H

#include <fstream>
#include <string>

#include "AttendanceCapture.h"
using namespace std;

class RotatingCodeCapture : public AttendanceCapture
{
private:
    string filePath;
    ifstream inputFile;

public:
    RotatingCodeCapture(const string& filePath);

    void beginSession() override;
    string captureNext() override;
    void endSession() override;

    ~RotatingCodeCapture() override = default;
};

#endif