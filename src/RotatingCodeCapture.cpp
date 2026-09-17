#include "RotatingCodeCapture.h"

#include <filesystem>
#include <stdexcept>

using namespace std;

RotatingCodeCapture::RotatingCodeCapture(const string& filePath)
    : filePath(filePath)
{
}

void RotatingCodeCapture::beginSession()
{
    if (!filesystem::exists(filePath))
    {
        throw runtime_error("Attendance file does not exist.");
    }

    inputFile.open(filePath);

    if (!inputFile.is_open())
    {
        throw runtime_error("Unable to open attendance file.");
    }
}

string RotatingCodeCapture::captureNext()
{
    string studentId;

    if (getline(inputFile, studentId))
    {
        return studentId;
    }

    return "";
}

void RotatingCodeCapture::endSession()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }
}