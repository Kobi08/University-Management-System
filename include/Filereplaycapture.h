#ifndef FILEREPLAYCAPTURE_H
#define FILEREPLAYCAPTURE_H

#include <fstream>
#include <string>

#include "AttendanceCapture.h"

class FileReplayCapture : public AttendanceCapture
{
private:
    std::string filePath;
    std::ifstream inputFile;

public:
    FileReplayCapture(const std::string& filePath);

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

    ~FileReplayCapture() override = default;
};

#endif