#include "AttendanceRegister.h"
#include "Exceptions.h"
#include "Enrolment.h"

using namespace std;

void AttendanceRegister::markpresent(Student& student,
                                     AttendanceSession& session)
{
    if (!session.isOpen())
    {
        throw SessionClosedException(
            "Cannot mark attendance: session is closed."
        );
    }

if (session.isExpired())
{
    throw SessionClosedException(
        "Cannot mark attendance: session has expired."
    );
}

    Course* course = session.getCourse();

    if (course == nullptr)
    {
        throw NotEnrolledException(
            "Cannot mark attendance: session has no course."
        );
    }

    bool enrolled = false;

    for (Enrolment* enrolment : course->viewEnrolment())
    {
        if (enrolment != nullptr &&
            enrolment->getStudent() == &student)
        {
            enrolled = true;
            break;
        }
    }

    if (!enrolled)
    {
        throw NotEnrolledException(
            "Cannot mark attendance: student is not enrolled."
        );
    }

    // ADD THE DUPLICATE CHECK HERE
    for (const AttendanceRecord& record : records)
    {
        if (record.student == &student &&
            record.session == &session)
        {
            throw DuplicateAttendanceException(
                "Cannot mark attendance: student is already marked present."
            );
        }
    }

    AttendanceRecord record(
        &student,
        &session,
        "Present",
        time(nullptr),
        "AttendanceRegister"
    );

    records.push_back(record);
}

void AttendanceRegister::addcorrections(AttendanceRecord rec,
                                         string reason,
                                         Lecturer lecturer)
{
    CorrectionRecord correction(
        rec,
        lecturer,
        reason,
        time(nullptr)
    );

    corrections.push_back(correction);
}

double AttendanceRegister::getstudentpercentage(Student& student,
                                                Course& course)
{
    int totalRecords = 0;
    int presentRecords = 0;

    for (const AttendanceRecord& record : records)
    {
        if (record.student != &student)
        {
            continue;
        }

        if (record.session == nullptr)
        {
            continue;
        }

        if (record.session->course != &course)
        {
            continue;
        }

        totalRecords++;

        if (record.status == "Present")
        {
            presentRecords++;
        }
    }

    if (totalRecords == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(presentRecords) /
            static_cast<double>(totalRecords)) * 100.0;
}

double AttendanceRegister::getcoursepercentage(Course& course)
{
    int totalRecords = 0;
    int presentRecords = 0;

    for (const AttendanceRecord& record : records)
    {
        if (record.session == nullptr)
        {
            continue;
        }

        if (record.session->course != &course)
        {
            continue;
        }

        totalRecords++;

        if (record.status == "Present")
        {
            presentRecords++;
        }
    }

    if (totalRecords == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(presentRecords) /
            static_cast<double>(totalRecords)) * 100.0;
}