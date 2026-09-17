#ifndef ATTENDANCEREGISTER_H
#define ATTENDANCEREGISTER_H

#include <list>
#include <string>

#include "AttendanceRecord.h"
#include "CorrectionRecord.h"

using namespace std;

class Student;
class AttendanceSession;
class Course;
class Lecturer;

class AttendanceRegister
{
private:
    list<AttendanceRecord> records;
    list<CorrectionRecord> corrections;

public:
    void markPresent(Student& student,
                     AttendanceSession& session);

    void addCorrections(AttendanceRecord& rec,
                        const string& reason,
                        Lecturer& lecturer);

    double getStudentPercentage(Student& student,
                                Course& course) const;

    double getCoursePercentage(Course& course) const;
};

#endif