#ifndef ATTENDANCEREGISTER_H
#define ATTENDANCEREGISTER_H

#include <list>
#include <string>
#include <vector>

#include "AttendanceRecord.h"
#include "CorrectionRecord.h"
#include "Student.h"
#include "AttendanceSession.h"
#include "Course.h"
#include "Lecturer.h"

class Menu;

class AttendanceRegister
{
private:
    friend class Menu;

    std::list<AttendanceRecord> records;
    std::list<CorrectionRecord> corrections;

    // References sessions owned by lecturers.
    std::vector<AttendanceSession*> sessions;

    std::string effectiveStatus(
        const AttendanceRecord& record
    ) const;

public:
    void registerSession(AttendanceSession& session);

    void markpresent(
        Student& student,
        AttendanceSession& session
    );

   void addcorrections(
    AttendanceRecord record,
    std::string reason,
    Lecturer& lecturer
);
    void correct(
        Student& student,
        AttendanceSession& session,
        Lecturer& lecturer,
        const std::string& status,
        const std::string& reason
    );

    double getstudentpercentage(
        Student& student,
        Course& course
    );

    double getcoursepercentage(Course& course);

    void showAudit() const;
};

#endif