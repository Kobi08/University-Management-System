#include "DuplicateattendanceException.h"

DuplicateattendanceException::DuplicateattendanceException()
    : Exception("Student attendance has already been recorded for this session.")
{
}