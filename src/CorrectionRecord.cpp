#include "CorrectionRecord.h"

using namespace std;

CorrectionRecord::CorrectionRecord(AttendanceRecord originalrecord,
                                   Lecturer actinglecuturer,
                                   const string& reason,
                                   time_t timestamp)
    : originalrecord(originalrecord),
      actinglecuturer(actinglecuturer),
      reason(reason),
      timestamp(timestamp)
{
}