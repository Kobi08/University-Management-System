#include "CorrectionRecord.h"

#include <ctime>

CorrectionRecord::CorrectionRecord(
    const AttendanceRecord& originalrecord,
    const Lecturer& actinglecturer,
    const string& reason)
    : originalrecord(originalrecord),
      actinglecturer(actinglecturer),
      reason(reason),
      timestamp(time(nullptr))
{
}