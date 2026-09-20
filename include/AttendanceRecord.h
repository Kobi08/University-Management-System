#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Student;
class AttendanceSession;
class AttendanceRegister;

class AttendanceRecord
{
private:
    Student* student;
    AttendanceSession* session;
    string status;
    time_t timestamp;
    string capturedby;
    friend class Menu;

public:
    AttendanceRecord(Student* student,
                     AttendanceSession* session,
                     const string& status,
                     time_t timestamp,
                     const string& capturedby);

    friend class AttendanceRegister;

    friend ostream& operator<<(ostream& os,
                               const AttendanceRecord& record);
};

#endif