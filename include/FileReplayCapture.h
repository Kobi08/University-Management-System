#ifndef FILEREPLAYCAPTURE_H
#define FILEREPLAYCAPTURE_H

#include <fstream>
#include <string>

#include "AttendanceCapture.h"

using namespace std;

class FileReplayCapture : public AttendanceCapture
{
private:
    string filePath;
    ifstream inputFile;

public:
    FileReplayCapture(const string& filePath);

    void beginSession() override;
    string captureNext() override;
    void endSession() override;

    ~FileReplayCapture() override = default;
};

#endif