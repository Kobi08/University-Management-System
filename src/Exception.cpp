#include "Exception.h"

Exception::Exception(const string& message)
    : message(message)
{
}

const char* Exception::what() const noexcept
{
    return message.c_str();
}