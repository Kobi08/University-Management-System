#include "CorrectionRecord.h"

using namespace std;

CorrectionRecord::CorrectionRecord(AttendanceRecord originalrecord,
                                   Lecturer actinglecuturer,
                                   const string& reason,
                                   time_t timestamp)
{
    this->originalrecord = originalrecord;
    this->actinglecuturer = actinglecuturer;
    this->reason = reason;
    this->timestamp = timestamp;
}