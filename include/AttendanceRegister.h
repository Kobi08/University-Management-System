#ifndef ATTENDANCEREGISTER_H
#define ATTENDANCEREGISTER_H

#include <iostream>
#include <list>

#include "AttendanceRecord.h"
#include "CorrectionRecord.h"
#include "Student.h"
#include "AttendanceSession.h"
#include "Course.h"
#include "Lecturer.h"

using namespace std;

class AttendanceRegister
{
private:
    list<AttendanceRecord> records;
    list<CorrectionRecord> corrections;

public:
    void markpresent(Student student,
                     AttendanceSession session);

    void addcorrections(AttendanceRecord rec,
                        string reason,
                        Lecturer lecturer);

    double getstudentpercentage(Student student,
                                Course course);

    double getcoursepercentage(Course course);
};

#endif