#include "FileReplayCapture.h"
#include "Exceptions.h"

FileReplayCapture::FileReplayCapture(const std::string& path)
    : filePath(path)
{
}

void FileReplayCapture::beginSession()
{
    // Close any previously opened file.
    endSession();

    // Clear previous errors or end-of-file state.
    inputFile.clear();

    inputFile.open(filePath);
    lineNumber = 0;

    if (!inputFile.is_open())
    {
        throw FileNotFoundException(
            "Cannot open replay file: " + filePath
        );
    }
}

std::string FileReplayCapture::captureNext()
{
    if (!inputFile.is_open())
    {
        throw PersistenceException(
            "Replay file is not open."
        );
    }

    std::string studentId;

    if (!std::getline(inputFile, studentId))
    {
        if (inputFile.bad())
        {
            throw PersistenceException(
                "Failed to read replay file."
            );
        }

        // An empty return value means the file has ended.
        return "";
    }

    ++lineNumber;

    // Handle Windows line endings when reading on other systems.
    if (!studentId.empty() && studentId.back() == '\r')
    {
        studentId.pop_back();
    }

    // Expected format: U followed by one or more digits.
    bool valid = studentId.size() >= 2 &&
                 studentId[0] == 'U';

    if (valid)
    {
        for (std::size_t i = 1; i < studentId.size(); ++i)
        {
            if (studentId[i] < '0' || studentId[i] > '9')
            {
                valid = false;
                break;
            }
        }
    }

    if (!valid)
    {
        throw CorruptDataException(
            "Invalid replay line " +
            std::to_string(lineNumber) +
            ": expected a student ID such as U003."
        );
    }

    return studentId;
}

void FileReplayCapture::endSession()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }
}