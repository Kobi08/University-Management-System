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
using namespace std;

int main(){ 
    Repository<Student> studentRepo("students.txt");

    Student student("Kamal", "1234");

    studentRepo.add(student);

    cout << "Student added successfully!" << endl;
    return 0;
}