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
#include "Repository.h"
#include "Menu.h"
using namespace std;

int main(){ 
       Student student("Kamal", "1234");
    Lecturer lecturer("Dr. Perera", "5678");

    Person* user1 = &student;
    Person* user2 = &lecturer;

    cout << "===== STUDENT TEST =====\n";

    if (user1->login("1234"))
    {
        cout << "Login successful.\n";
        user1->showMenu();
    }
    else
    {
        cout << "Login failed.\n";
    }


    cout << "\n===== LECTURER TEST =====\n";

    if (user2->login("5678"))
    {
        cout << "Login successful.\n";
        user2->showMenu();
    }
    else
    {
        cout << "Login failed.\n";
    }


    cout << "\n===== WRONG PASSWORD TEST =====\n";

    if (user1->login("wrong"))
    {
        cout << "ERROR: Wrong password accepted!\n";
    }
    else
    {
        cout << "Wrong password correctly rejected.\n";
    }
    return 0;
}