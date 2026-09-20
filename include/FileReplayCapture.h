#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include <fstream>
#include <string>

#include "AttendanceCapture.h"

class FileReplayCapture : public AttendanceCapture
{
private:
    std::string filePath;
    std::ifstream inputFile;
    unsigned int lineNumber = 0;

public:
    explicit FileReplayCapture(const std::string& path);

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

        std::string name() const override
    {
        return "FileReplay";
    }

    ~FileReplayCapture() override = default;
};

#endif