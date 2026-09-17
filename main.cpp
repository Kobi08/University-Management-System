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
using namespace std;

int main(){
      //Testing for Time slot
    //cout<<"University Management System PROJECT 1";

    //TimeSlot slot1("Monday",9,11,"Lab A");
    //TimeSlot slot2("Monday",10,12,"LT-3");
    //TimeSlot slot3("Tuesday",9,11,"Lab B");

    //cout<<"Slot 1: "<<slot1<<std::endl;
    //cout<<"Slot 2: "<<slot2<<std::endl;
    //cout<<"Slot 3: "<<slot3<<std::endl;

    //cout<<"\nSlot1 clashes Slot2: "
      //       <<(slot1==slot2)<<endl;

    //cout<<"Slot1 clashes Slot3: "
      //       <<(slot1==slot3)<<endl;


// Lecturer l("Dr. Silva", "lect123");

// cout << l << endl;

// l.showMenu();

// cout << l.login("lect123") << endl;



    // Administrator admin("Admin", "admin123");

    // cout << admin << endl;

    // admin.showMenu();

    // cout << "\nLogin test: "
    //      << admin.login("admin123")
    //      << endl;

    // admin.logout();

  

//     // You'll need to construct a Course according
//     // to your existing Course hierarchy.

//     Student student("Kobi", "1234");

//     cout << student << endl;

// FileReplayCapture replay("attendance.txt");

// replay.beginSession();

// cout << replay.captureNext() << endl;
// cout << replay.captureNext() << endl;
// cout << replay.captureNext() << endl;

// replay.endSession();

 try
    {
        throw SessionclosedException();
    }
    catch (const Exception& e)
    {
        cout << e.what() << endl;
    }

    try
    {
        throw NotenrolException();
    }
    catch (const Exception& e)
    {
        cout << e.what() << endl;
    }

    try
    {
        throw DuplicateattendanceException();
    }
    catch (const Exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}