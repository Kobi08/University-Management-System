#include <iostream>
#include "TimeSlot.h"
#include "Course.h"
#include "AssessmentMarks.h"
#include "LabCourse.h"
#include "LectureCourse.h"
#include "Person.h"
#include "ProjectCourse.h"
#include "Timetable.h"
#include "Lecturer.h"
#include "Student.h"
#include "Administrator.h"
#include "Enrolment.h"
#include "AttendanceSession.h"
#include "Attendancecapture.h"
#include "Filereplaycapture.h"
#include "Attendancerecord.h"
#include "Attendanceregister.h"
#include "Correctionrecord.h"
#include "SessionclosedException.h"
#include "NotenrolException.h"
#include "DuplicateattendanceException.h"
#include "Rotatingcodecapture.h"
using namespace std;

int main(){ 
    cout << "===== RotatingCodeCapture Test =====\n\n";

    RotatingCodeCapture capture;

    // Test 1: Start the session
    capture.beginSession();

    // Test 2: Enter a code
    string enteredCode = capture.captureNext();

    cout << "\nYou entered: " << enteredCode << endl;

    // Test 3: End the session
    capture.endSession();

    cout << "\nSession ended successfully.\n";
    return 0;
}