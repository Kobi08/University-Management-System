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
// Thrown when a student tries to mark attendance
// for a course they are not enrolled in.
class NotEnrolledException : public Exception
{
public:
    explicit NotEnrolledException(const string& message)
        : Exception(message)
    {
    }
};

// Thrown when a student tries to mark attendance
// more than once for the same attendance session.
class DuplicateAttendanceException : public Exception
{
public:
    explicit DuplicateAttendanceException(const string& message)
        : Exception(message)
    {
    }
};

// Thrown when attendance is attempted after
// the attendance session has been closed.
class SessionClosedException : public Exception
{
public:
    explicit SessionClosedException(const string& message)
        : Exception(message)
    {
    }
};

#endif