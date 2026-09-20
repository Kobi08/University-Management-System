#include <iostream>
#include <cassert>
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
    //   Menu menu;
    // menu.run();
   
    try
    {
        Menu menu;
        menu.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << "Application error: "
                  << error.what()
                  << '\n';

        return 1;
    }
    return 0;
}

