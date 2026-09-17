#include "AttendanceRecord.h"

#include "Student.h"
#include "AttendanceSession.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

AttendanceRecord::AttendanceRecord(Student& student,
                                   AttendanceSession& session,
                                   const string& status,
                                   time_t timestamp,
                                   const string& capturedby)
    : student(&student),
      session(&session),
      status(status),
      timestamp(timestamp),
      capturedby(capturedby)
{
}

ostream& operator<<(ostream& os,
                    const AttendanceRecord& r)
{
    os << "Attendance Record"
       << "\nStudent: " << r.student->getName()
       << "\nStatus: " << r.status
       << "\nCaptured By: " << r.capturedby
       << "\nTimestamp: "
       << put_time(localtime(&r.timestamp),
                   "%Y-%m-%d %H:%M:%S");

    return os;
}