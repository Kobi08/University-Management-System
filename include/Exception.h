#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class Exception : public exception
{
private:
    string message;

public:
    Exception(const string& message);

    const char* what() const noexcept override;
};

#endif