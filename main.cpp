#include <iostream>
#include <list>

#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "AssessmentMarks.h"
#include "Enrolment.h"
#include "Exceptions.h"
#include "AttendanceRegister.h"

using namespace std;

int main()
{
    Student student("Priyanka", "student123");
    Lecturer lecturer("Lecturer One", "lecturer123");
    Administrator administrator("Admin One", "admin123");

    // ==================== PERSON HIERARCHY TEST ====================

    cout << "===== PERSON HIERARCHY TEST =====\n\n";

    cout << "Student Name: " << student.getName() << endl;
    cout << "Student ID: " << student.getId() << endl;
    cout << "Student Login: "
         << (student.login("student123") ? "Successful" : "Failed")
         << endl;

    cout << "\nLecturer Name: " << lecturer.getName() << endl;
    cout << "Lecturer ID: " << lecturer.getId() << endl;
    cout << "Lecturer Login: "
         << (lecturer.login("lecturer123") ? "Successful" : "Failed")
         << endl;

    cout << "\nAdministrator Name: " << administrator.getName() << endl;
    cout << "Administrator ID: " << administrator.getId() << endl;
    cout << "Administrator Login: "
         << (administrator.login("admin123") ? "Successful" : "Failed")
         << endl;

    cout << "\n===== POLYMORPHISM TEST =====\n";

    Person* people[] = {
        &student,
        &lecturer,
        &administrator
    };

    for (Person* person : people)
    {
        person->showMenu();
    }

    // ==================== COURSE HIERARCHY TEST ====================

    cout << "\n===== COURSE HIERARCHY TEST =====\n\n";

   LectureCourse lectureCourse(
    "CO2201",
    "Object Oriented Programming",
    3,
    50,
    lecturer,
    {"CO1101", "CO1102"}
);

    LabCourse labCourse(
        "CO2202",
        "Programming Lab",
        2,
        30,
        lecturer
    );

    ProjectCourse projectCourse(
        "CO2203",
        "OOP Project",
        4,
        20,
        lecturer
    );

    cout << "Lecture Course Type: "
         << lectureCourse.getCourseType() << endl;

    cout << "Lab Course Type: "
         << labCourse.getCourseType() << endl;

    cout << "Project Course Type: "
         << projectCourse.getCourseType() << endl;

    // ==================== ASSESSMENT MARKS TEST ====================

    cout << "\n===== ASSESSMENT MARKS TEST =====\n\n";

    AssessmentMarks lectureMarks;
    lectureMarks.setCAScore(80);
    lectureMarks.setExamScore(70);

    AssessmentMarks labMarks;
    labMarks.setPracticalMarks({70, 80, 75});

    AssessmentMarks projectMarks;
    projectMarks.setSubmissionScore(90);

    cout << "Lecture CA: "
         << lectureMarks.getCAScore() << endl;

    cout << "Lecture Exam: "
         << lectureMarks.getExamScore() << endl;

    cout << "Project Submission: "
         << projectMarks.getSubmissionScore() << endl;

    // ==================== POLYMORPHIC GRADING TEST ====================

    cout << "\n===== POLYMORPHIC GRADING TEST =====\n\n";

    cout << "Lecture Grade: "
         << lectureCourse.calculateGrade(lectureMarks) << endl;

    cout << "Lab Grade: "
         << labCourse.calculateGrade(labMarks) << endl;

    cout << "Project Grade: "
         << projectCourse.calculateGrade(projectMarks) << endl;

    // ==================== ENROLMENT TEST ====================

    cout << "\n===== ENROLMENT TEST =====\n\n";

    Enrolment lectureEnrolment(
        student,
        lectureCourse,
        "Enrolled",
        "2026-09-18",
        0
    );

    lectureEnrolment.setAssessmentMarks(lectureMarks);
    lectureEnrolment.calculateGrade();

    cout << lectureEnrolment << endl;

    cout << "\nEnrolment Grade: "
         << lectureEnrolment.getGrade() << endl;

    cout << "Enrolment Completed: "
         << (lectureEnrolment.isCompleted() ? "Yes" : "No")
         << endl;

         student.logout();
lecturer.logout();
administrator.logout();

cout << "\n===== COURSE BASIC FUNCTIONS TEST =====\n";

cout << "Lecture Course Code: "
     << lectureCourse.getCode() << endl;

cout << "Lecture Course Full: "
     << (lectureCourse.isFull() ? "Yes" : "No") << endl;

cout << "Has CO1001 as prerequisite: "
     << (lectureCourse.hasPrerequisites("CO1001") ? "Yes" : "No")
     << endl;

cout << "Has CO2201 as prerequisite: "
     << (lectureCourse.hasPrerequisites("CO2201") ? "Yes" : "No")
     << endl;

cout << "Has CO1101 as prerequisite: "
     << (lectureCourse.hasPrerequisites("CO1101") ? "Yes" : "No")
     << endl;

cout << "\nCourse Operator<< Test:\n";
cout << lectureCourse << endl;

lectureCourse.addEnrolment(lectureEnrolment);

cout << "\nEnrolment List Size: "
     << lectureCourse.viewEnrolment().size() << endl;
    
cout << "\n===== EXCEPTION HIERARCHY TEST =====\n";

try
{
    throw CourseFullException("Course is full.");
}
catch (const Exception& e)
{
    cout << "CourseFullException caught: "
         << e.what() << endl;
}

try
{
    throw PrerequisiteNotMetException(
        "Prerequisite not completed."
    );
}
catch (const Exception& e)
{
    cout << "PrerequisiteNotMetException caught: "
         << e.what() << endl;
}

try
{
    throw TimetableClashException(
        "Timetable clash detected."
    );
}
catch (const Exception& e)
{
    cout << "TimetableClashException caught: "
         << e.what() << endl;
}


cout << "\n===== COURSE FULL ENROLMENT TEST =====\n";

LectureCourse fullCourse(
    "CO9999",
    "Full Test Course",
    3,
    1,
    lecturer
);

Enrolment existingEnrolment(
    student,
    fullCourse,
    "Enrolled",
    "2026-09-18",
    0
);

fullCourse.addEnrolment(existingEnrolment);

try
{
    student.enrollCourse(fullCourse);
}
catch (const CourseFullException& e)
{
    cout << "CourseFullException caught: "
         << e.what() << endl;
}

cout << "\n===== STUDENT ENROLMENT FLOW TEST =====\n";

LectureCourse testCourse(
    "CO3001",
    "Test Course",
    3,
    10,
    lecturer
);

student.enrollCourse(testCourse);

cout << "Enrolment List Size After Student Enrolment: "
     << testCourse.viewEnrolment().size() << endl;
student.dropCourse(testCourse);

cout << "Enrolment List Size After Student Drop: "
     << testCourse.viewEnrolment().size() << endl;     

     cout << "\n===== ENROLMENT GETTER TEST =====\n";

Student* enrolledStudent = lectureEnrolment.getStudent();

cout << "Enrolment Student: "
     << enrolledStudent->getName() << endl;

cout << "Enrolment Student ID: "
     << enrolledStudent->getId() << endl;
     cout << "\nEnrolment Course: "
     << lectureEnrolment.getCourse()->getCode() << endl;

cout << "\n===== ATTENDANCE TEST =====\n";

TimeSlot lectureSlot(
    "Monday",
    9,
    11,
    "LT-3"
);

lectureCourse.addTimeSlot(lectureSlot);

lecturer.addCourse(lectureCourse);

Enrolment attendanceEnrolment(
    student,
    lectureCourse,
    "Enrolled",
    "2026-09-19",
    0
);

lectureCourse.addEnrolment(attendanceEnrolment);
Student otherStudent("Other Student", "other123");
lecturer.openAttendanceSession(lectureSlot, 60);

AttendanceRegister attendanceRegister;

attendanceRegister.markpresent(
    student,
    *lecturer.getActiveSession()
);

cout << "Attendance marked successfully." << endl;
try
{
    attendanceRegister.markpresent(
        student,
        *lecturer.getActiveSession()
    );
}
catch (const DuplicateAttendanceException& e)
{
    cout << "DuplicateAttendanceException caught: "
         << e.what() << endl;
}
try
{
    attendanceRegister.markpresent(
        otherStudent,
        *lecturer.getActiveSession()
    );
}
catch (const NotEnrolledException& e)
{
    cout << "NotEnrolledException caught: "
         << e.what() << endl;
}

lecturer.closeAttendanceSession();
AttendanceSession closedSession(
    lectureCourse,
    lectureSlot,
    60
);

try
{
    attendanceRegister.markpresent(
        student,
        closedSession
    );
}
catch (const SessionClosedException& e)
{
    cout << "SessionClosedException caught: "
         << e.what() << endl;
}
return 0;


   
}