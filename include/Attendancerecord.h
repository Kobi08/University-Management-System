#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Student;
class AttendanceSession;

class AttendanceRecord
{
private:
    Student* student;
    AttendanceSession* session;
    string status;
    time_t timestamp;
    string capturedby;

public:
    AttendanceRecord(Student& student,
                     AttendanceSession& session,
                     const string& status,
                     time_t timestamp,
                     const string& capturedby);

    friend ostream& operator<<(ostream& os,
                               const AttendanceRecord& r);
};

#endif