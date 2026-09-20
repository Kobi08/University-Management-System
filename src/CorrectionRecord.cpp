#include "CorrectionRecord.h"

CorrectionRecord::CorrectionRecord(
    AttendanceRecord originalrecord,
    Lecturer& actinglecuturer,
    const std::string& reason,
    std::time_t timestamp,
    const std::string& correctedStatus)
    : originalrecord(originalrecord),
      actinglecuturer(&actinglecuturer),
      correctedStatus(correctedStatus),
      reason(reason),
      timestamp(timestamp)
{
}