#include "FileReplayCapture.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

using namespace std;

FileReplayCapture::FileReplayCapture(const string& filePath)
    : filePath(filePath)
{
}

void FileReplayCapture::beginSession()
{
    inputFile.open(filePath);

    if (!inputFile.is_open())
    {
        throw runtime_error("Unable to open replay file.");
    }
}

string FileReplayCapture::captureNext()
{
    string studentId;

    if (getline(inputFile, studentId))
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