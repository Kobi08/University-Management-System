#include "AttendanceRegister.h"
#include "Exceptions.h"
#include "Enrolment.h"

#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

void AttendanceRegister::registerSession(
    AttendanceSession& session)
{
    for (AttendanceSession* existing : sessions)
    {
        if (existing == &session)
        {
            return;
        }
    }

    sessions.push_back(&session);
}

void AttendanceRegister::markpresent(
    Student& student,
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

    Course* course =
        session.getCourse();

    if (course == nullptr)
    {
        throw Exception(
            "Attendance session has no course."
        );
    }

    bool enrolled = false;

    for (Enrolment* enrolment :
         course->viewEnrolment())
    {
        if (enrolment != nullptr &&
            enrolment->student == &student &&
            enrolment->status == "Enrolled")
        {
            enrolled = true;
            break;
        }
    }

    if (!enrolled)
    {
        throw NotEnrolledException(
            "Cannot mark attendance: student is not currently enrolled."
        );
    }

    for (const AttendanceRecord& record :
         records)
    {
        if (record.student == &student &&
            record.session == &session)
        {
            throw DuplicateAttendanceException(
                "Cannot mark attendance: student is already marked "
                "for this session."
            );
        }
    }

    AttendanceRecord record(
        &student,
        &session,
        "Present",
        time(nullptr),
        session.captureName()
    );

    records.push_back(record);
}

void AttendanceRegister::addcorrections(
    AttendanceRecord record,
    string reason,
    Lecturer& lecturer)
{
    CorrectionRecord correction(
        record,
        lecturer,
        reason,
        time(nullptr)
    );

    corrections.push_back(
        correction
    );
}

string AttendanceRegister::effectiveStatus(
    const AttendanceRecord& record) const
{
    string result =
        record.status;

    for (const CorrectionRecord& correction :
         corrections)
    {
        if (correction.originalrecord.student ==
                record.student &&
            correction.originalrecord.session ==
                record.session)
        {
            result =
                correction.correctedStatus;
        }
    }

    return result;
}

void AttendanceRegister::correct(
    Student& student,
    AttendanceSession& session,
    Lecturer& lecturer,
    const string& status,
    const string& reason)
{
    if (status != "Present" &&
        status != "Late" &&
        status != "Absent")
    {
        throw Exception(
            "Correction status must be "
            "Present, Late, or Absent."
        );
    }

    if (reason.empty())
    {
        throw Exception(
            "A correction reason is required."
        );
    }

    for (const AttendanceRecord& record :
         records)
    {
        if (record.student == &student &&
            record.session == &session)
        {
            CorrectionRecord correction(
                record,
                lecturer,
                reason,
                time(nullptr),
                status
            );

            corrections.push_back(
                correction
            );

            return;
        }
    }

    throw Exception(
        "No attendance record exists for this "
        "student in that session."
    );
}

double AttendanceRegister::getstudentpercentage(
    Student& student,
    Course& course)
{
    int totalSessions = 0;
    int attendedSessions = 0;

    for (AttendanceSession* session :
         sessions)
    {
        if (session == nullptr ||
            session->getCourse() != &course)
        {
            continue;
        }

        bool eligible = false;

        for (const string& studentId :
             session->eligibleStudents())
        {
            if (studentId ==
                student.getId())
            {
                eligible = true;
                break;
            }
        }

        if (!eligible)
        {
            continue;
        }

        ++totalSessions;

        for (const AttendanceRecord& record :
             records)
        {
            if (record.student != &student ||
                record.session != session)
            {
                continue;
            }

            const string status =
                effectiveStatus(record);

            if (status == "Present" ||
                status == "Late")
            {
                ++attendedSessions;
            }

            break;
        }
    }

    if (totalSessions == 0)
    {
        return 0.0;
    }

    return
        (static_cast<double>(attendedSessions) /
         static_cast<double>(totalSessions))
        * 100.0;
}

double AttendanceRegister::getcoursepercentage(
    Course& course)
{
    int totalOpportunities = 0;
    int attended = 0;

    for (AttendanceSession* session :
         sessions)
    {
        if (session == nullptr ||
            session->getCourse() != &course)
        {
            continue;
        }

        totalOpportunities +=
            static_cast<int>(
                session->eligibleStudents().size()
            );

        for (const AttendanceRecord& record :
             records)
        {
            if (record.session != session)
            {
                continue;
            }

            const string status =
                effectiveStatus(record);

            if (status == "Present" ||
                status == "Late")
            {
                ++attended;
            }
        }
    }

    if (totalOpportunities == 0)
    {
        return 0.0;
    }

    return
        (static_cast<double>(attended) /
         static_cast<double>(totalOpportunities))
        * 100.0;
}

void AttendanceRegister::showAudit() const
{
    cout << "\n===== ATTENDANCE CORRECTION AUDIT =====\n";

    if (corrections.empty())
    {
        cout << "No attendance corrections recorded.\n";
        return;
    }

    for (const CorrectionRecord& correction :
         corrections)
    {
        const AttendanceRecord& original =
            correction.originalrecord;

        cout << "\nStudent: ";

        if (original.student != nullptr)
        {
            cout << original.student->getId()
                 << " - "
                 << original.student->getName();
        }
        else
        {
            cout << "Unknown";
        }

        cout << "\nOriginal status: "
             << original.status;

        cout << "\nCorrected status: "
             << correction.correctedStatus;

        cout << "\nActing lecturer: ";

        if (correction.actinglecuturer != nullptr)
        {
            cout << correction.actinglecuturer->getId()
                 << " - "
                 << correction.actinglecuturer->getName();
        }
        else
        {
            cout << "Unknown";
        }

        cout << "\nReason: "
             << correction.reason;

        cout << "\nTimestamp: "
             << correction.timestamp;

        cout << "\n";
    }
}