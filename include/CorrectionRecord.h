#ifndef CORRECTIONRECORD_H
#define CORRECTIONRECORD_H

#include <string>
#include <ctime>

#include "AttendanceRecord.h"
#include "Lecturer.h"

using namespace std;

class CorrectionRecord
{
private:
    AttendanceRecord originalrecord;
    Lecturer actinglecuturer;
    string reason;
    time_t timestamp;

public:
    CorrectionRecord(AttendanceRecord originalrecord,
                     Lecturer actinglecuturer,
                     const string& reason,
                     time_t timestamp);
};

#endif