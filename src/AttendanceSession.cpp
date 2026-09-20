#include "AttendanceSession.h"
#include "AttendanceCapture.h"
#include "Enrolment.h"
#include "Student.h"
#include "Exceptions.h"

#include <algorithm>
#include <utility>

AttendanceSession::AttendanceSession()
    : course(nullptr),
      timeslot(),
      opentime(0),
      isopen(false),
      durationminute(0),
      capture(nullptr)
{
}

AttendanceSession::AttendanceSession(
    Course& course,
    const TimeSlot& timeslot,
    int durationminute)
    : course(&course),
      timeslot(timeslot),
      opentime(0),
      isopen(false),
      durationminute(durationminute),
      capture(nullptr)
{
    if (durationminute <= 0)
    {
        throw Exception(
            "Session duration must be greater than zero."
        );
    }
}

void AttendanceSession::open()
{
    if (isopen)
    {
        return;
    }

    if (course == nullptr || durationminute <= 0)
    {
        throw Exception(
            "Cannot open an unconfigured attendance session."
        );
    }

    // Prepare a snapshot of the currently enrolled students.
    std::vector<std::string> studentIds;

   for (const Enrolment* enrolment :
     course->viewEnrolment())
{
    if (enrolment == nullptr ||
        enrolment->getStudent() == nullptr ||
        enrolment->status != "Enrolled")
    {
        continue;
    }

        const std::string id =
            enrolment->getStudent()->getId();

        // Count each student only once.
        if (std::find(
                studentIds.begin(),
                studentIds.end(),
                id) == studentIds.end())
        {
            studentIds.push_back(id);
        }
    }

    // Opening a replay file may throw.
    // Do this before marking the session open.
    if (capture != nullptr)
    {
        capture->beginSession();
    }

    eligibleStudentIds = std::move(studentIds);

    opentime = std::time(nullptr);
    isopen = true;
}

void AttendanceSession::close()
{
    if (capture != nullptr)
    {
        capture->endSession();
    }

    isopen = false;
}

bool AttendanceSession::isExpired()
{
    if (!isopen)
    {
        return false;
    }

    const bool expired =
        std::difftime(
            std::time(nullptr),
            opentime
        ) >= durationminute * 60.0;

    if (expired)
    {
        close();
    }

    return expired;
}

bool AttendanceSession::isOpen() const
{
    return isopen;
}

Course* AttendanceSession::getCourse() const
{
    return course;
}

const TimeSlot& AttendanceSession::getTimeSlot() const
{
    return timeslot;
}

const std::vector<std::string>&
AttendanceSession::eligibleStudents() const
{
    return eligibleStudentIds;
}

void AttendanceSession::setcapturemethod(
    AttendanceCapture* c)
{
    if (c == capture)
    {
        return;
    }

    // This function takes ownership of the supplied pointer.
    if (isopen)
    {
        delete c;

        throw Exception(
            "Choose the capture method before opening the session."
        );
    }

    delete capture;
    capture = c;
}

std::string AttendanceSession::captureNext()
{
    if (!isopen || isExpired())
    {
        throw SessionClosedException(
            "Cannot capture attendance: session is closed or expired."
        );
    }

    if (capture == nullptr)
    {
        throw Exception(
            "No attendance capture method has been selected."
        );
    }

    return capture->captureNext();
}

std::string AttendanceSession::captureName() const
{
    if (capture == nullptr)
    {
        return "None";
    }

    return capture->name();
}

AttendanceSession::AttendanceSession(
    AttendanceSession&& other)
    : AttendanceSession()
{
    *this = std::move(other);
}

AttendanceSession& AttendanceSession::operator=(
    AttendanceSession&& other)
{
    if (this != &other)
    {
        timeslot = other.timeslot;

        delete capture;

        course = other.course;
        opentime = other.opentime;
        isopen = other.isopen;
        durationminute = other.durationminute;

        capture = other.capture;

        eligibleStudentIds =
            std::move(other.eligibleStudentIds);

        other.capture = nullptr;
        other.course = nullptr;
        other.opentime = 0;
        other.isopen = false;
        other.durationminute = 0;
    }

    return *this;
}

AttendanceSession::~AttendanceSession()
{
    delete capture;
}