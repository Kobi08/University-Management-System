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
    Lecturer actinglecturer;
    string reason;
    time_t timestamp;

public:
    CorrectionRecord(const AttendanceRecord& originalrecord,
                     const Lecturer& actinglecturer,
                     const string& reason);
};

#endif