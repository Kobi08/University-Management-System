#include "RotatingCodeCapture.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

RotatingCodeCapture::RotatingCodeCapture()
    : currentCode("")
{
}

void RotatingCodeCapture::beginSession()
{
    srand(static_cast<unsigned>(time(nullptr)));

    currentCode = to_string(100000 + rand() % 900000);

    cout << "Current Attendance Code: "
         << currentCode
         << endl;
}

string RotatingCodeCapture::captureNext()
{
    string enteredCode;

    cout << "Enter attendance code: ";
    cin >> enteredCode;

    return enteredCode;
}

void RotatingCodeCapture::endSession()
{
    currentCode.clear();
}