#include "AttendanceRegister.h"

#include "Student.h"
#include "AttendanceSession.h"
#include "AttendanceRecord.h"
#include "CorrectionRecord.h"
#include "Course.h"
#include "Lecturer.h"

#include "SessionclosedException.h"
#include "NotenrolException.h"
#include "DuplicateattendanceException.h"

using namespace std;

void AttendanceRegister::markPresent(Student& student,
                                     AttendanceSession& session)
{
    // Check whether session is open
    if (!session.isopen)
    {
        throw SessionclosedException();
    }

    // Check whether student is enrolled
    if (!student.isEnrolled(*session.course))
    {
        throw NotenrolException();
    }

    // Check duplicate attendance
    for (const AttendanceRecord& record : records)
    {
        if (record.student == &student &&
            record.session == &session)
        {
            throw DuplicateattendanceException();
        }
    }

    // Create a new attendance record
    AttendanceRecord record(
        student,
        session,
        "Present",
        time(nullptr),
        "RotatingCode"
    );

    records.push_back(record);
}


void AttendanceRegister::addCorrections(
    AttendanceRecord& rec,
    const string& reason,
    Lecturer& lecturer)
{
    CorrectionRecord correction(
        rec,
        lecturer,
        reason
    );

    corrections.push_back(correction);
}


double AttendanceRegister::getStudentPercentage(
    Student& student,
    Course& course) const
{
    int total = 0;
    int present = 0;

    for (const AttendanceRecord& record : records)
    {
        if (record.student == &student &&
            record.session->course == &course)
        {
            total++;

            if (record.status == "Present")
            {
                present++;
            }
        }
    }

    if (total == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(present) / total) * 100.0;
}


double AttendanceRegister::getCoursePercentage(
    Course& course) const
{
    int total = 0;
    int present = 0;

    for (const AttendanceRecord& record : records)
    {
        if (record.session->course == &course)
        {
            total++;

            if (record.status == "Present")
            {
                present++;
            }
        }
    }

    if (total == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(present) / total) * 100.0;
}