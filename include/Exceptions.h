#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

// Base exception class for domain-level rule violations.
class Exception : public runtime_error
{
public:
    explicit Exception(const string& message)
        : runtime_error(message)
    {
    }
};

// Thrown when a student tries to enrol in a course
// that has already reached its capacity.
class CourseFullException : public Exception
{
public:
    explicit CourseFullException(const string& message)
        : Exception(message)
    {
    }
};

// Thrown when a student has not completed
// the required prerequisite courses.
class PrerequisiteNotMetException : public Exception
{
public:
    explicit PrerequisiteNotMetException(const string& message)
        : Exception(message)
    {
    }
};

// Thrown when a course creates a timetable clash
// with the student's existing timetable.
class TimetableClashException : public Exception
{
public:
    explicit TimetableClashException(const string& message)
        : Exception(message)
    {
    }
};

#endif