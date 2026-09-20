#ifndef CORRECTIONRECORD_H
#define CORRECTIONRECORD_H

#include <string>
#include <ctime>

#include "AttendanceRecord.h"

class Lecturer;
class AttendanceRegister;
class Menu;

class CorrectionRecord
{
private:
    friend class AttendanceRegister;
    friend class Menu;

    AttendanceRecord originalrecord;

    // Refers to the existing lecturer; does not own the lecturer.
    Lecturer* actinglecuturer;

    std::string correctedStatus;
    std::string reason;
    std::time_t timestamp;

public:
    CorrectionRecord(
        AttendanceRecord originalrecord,
        Lecturer& actinglecuturer,
        const std::string& reason,
        std::time_t timestamp,
        const std::string& correctedStatus = "Present"
    );
};

#endif