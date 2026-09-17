#include "FileReplayCapture.h"
#include <filesystem>
#include <iostream>

#include <stdexcept>

FileReplayCapture::FileReplayCapture(const std::string& filePath)
    : filePath(filePath)
{
}


void FileReplayCapture::beginSession()
{
    inputFile.open(filePath);

    if (!inputFile.is_open())
    {
        throw std::runtime_error("Unable to open replay file.");
    }
}

std::string FileReplayCapture::captureNext()
{
    std::string studentId;

    if (std::getline(inputFile, studentId))
    {
        return studentId;
    }

    return "";
}

void FileReplayCapture::endSession()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }
}