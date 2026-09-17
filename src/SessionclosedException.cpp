#include "SessionclosedException.h"

SessionclosedException::SessionclosedException()
    : Exception("Attendance session is closed or expired.")
{
}