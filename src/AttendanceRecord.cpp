#include "AttendanceRecord.h"

using namespace std;

AttendanceRecord::AttendanceRecord(Student* student,
                                   AttendanceSession* session,
                                   const string& status,
                                   time_t timestamp,
                                   const string& capturedby)
{
    this->student = student;
    this->session = session;
    this->status = status;
    this->timestamp = timestamp;
    this->capturedby = capturedby;
}

ostream& operator<<(ostream& os,
                    const AttendanceRecord& record)
{
    os << "AttendanceRecord [Status: "
       << record.status
       << ", Timestamp: "
       << record.timestamp
       << ", Captured By: "
       << record.capturedby
       << "]";

    return os;
}