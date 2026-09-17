#include "AttendanceRegister.h"

#include "Student.h"
#include "AttendanceSession.h"
#include "Course.h"
#include "Lecturer.h"

using namespace std;

void AttendanceRegister::markPresent(Student& student,
                                     AttendanceSession& session)
{
    // Validation and duplicate checking will be added
    // when the attendance exceptions and capture mechanism
    // are connected.
}

void AttendanceRegister::addCorrections(AttendanceRecord& rec,
                                         const string& reason,
                                         Lecturer& lecturer)
{
    CorrectionRecord correction(rec, lecturer, reason);
    corrections.push_back(correction);
}

double AttendanceRegister::getStudentPercentage(Student& student,
                                                Course& course) const
{
    // Attendance percentage calculation will be connected
    // after the session/record relationships are fully exposed.
    return 0.0;
}

double AttendanceRegister::getCoursePercentage(Course& course) const
{
    // Attendance percentage calculation will be connected
    // after the session/record relationships are fully exposed.
    return 0.0;
}
