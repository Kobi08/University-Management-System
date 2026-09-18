#ifndef CORRECTIONRECORD_H
#define CORRECTIONRECORD_H

#include <string>
#include <ctime>

using namespace std;

class AttendanceRecord;
class Lecturer;

class CorrectionRecord
{
private:
    AttendanceRecord* originalrecord;
    Lecturer* actinglecuturer;
    string reason;
    time_t timestamp;

public:
    CorrectionRecord(AttendanceRecord* originalrecord,
                     Lecturer* actinglecuturer,
                     const string& reason,
                     time_t timestamp);
};

#endif