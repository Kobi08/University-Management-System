University Course Registration, Timetable & Attendance Management System
-------------------------------------------------------------------------

CO2203 – Object Oriented Programming Group Project

A console-based C++17 university management system supporting Student, Lecturer, and Administrator roles. The system provides course registration, prerequisite and capacity validation, timetable clash detection, course administration, attendance capture and reporting, correction audit trails, and file-based persistence.

-----------------------------
Team
- P. Kobisan – 24/ENG/075
- R. Priyanka – 24/ENG/118
- I. Rathigan – 24/ENG/124
-----------------------------


Main Features
- Polymorphic login and role-specific menus through the abstract Person hierarchy.
- Administrator user CRUD and course CRUD.
- Three course types: LectureCourse, LabCourse, and ProjectCourse.
- Student enrolment and course dropping with capacity, recursive prerequisite, and timetable-clash validation.
- Weekly timetable display using TimeSlot objects and overloaded clash comparison.
- Lecturer-only enrolment viewing for assigned courses.
- Attendance sessions with configurable duration and automatic expiry.
- Runtime-selectable attendance capture through the abstract AttendanceCapture interface:
  - RotatingCodeCapture
  - FileReplayCapture
- Attendance validation for closed/expired sessions, non-enrolled students, and duplicate attendance.
- Immutable attendance records with append-only correction/audit records.
- Per-student and per-course attendance percentages.
- File persistence through the generic Repository<T> interface.
- Custom exception hierarchy for domain and persistence errors.


Build Requirements
- C++17 compiler
- CMake 3.10 or newer
- g++/MinGW or another C++17-compatible compiler

Build
Run the following commands from the project root directory:

cmake -S . -B build
cmake --build build

Run on Windows / MinGW
.\build\UniversityManagementSystem.exe

Run on Linux/macOS
./build/UniversityManagementSystem

The program should be run from the project root so that relative paths such as data/students.txt and data/courses.txt 
resolve correctly.

-----------------------------------------------------------------------------------------------------------------------------
Sample Login Credentials
Role	       User ID	Password
Student         U001	1111
Student         U004	Kobisan26
Lecturer        U002	2222
Administrator	U003	3333
-----------------------------------------------------------------------------------------------------------------------------

Sample Data
The data/ directory contains the persistent text files used by the program:
- students.txt
- lecturers.txt
- administrators.txt
- courses.txt
- enrolments.txt
- attendance_sessions.txt
- attendance_records.txt
- attendance_corrections.txt
- replay.txt

----------------------------------------------------------------------------------
File Formats

1.Users:
UserID|Name|Password

2.Courses:
Type|Code|Title|Credits|Capacity|LecturerID|Prerequisites|TimeSlots

Example:
Lecture|CO2203|Object Oriented Programming|3|50|U002|CO1101|Monday,10,12,Hall B

Multiple prerequisites are comma-separated. Multiple time slots are semicolon-separated.

3.Enrolments:
StudentID|CourseCode|Status|DateEnrolled|Grade

4.Attendance sessions:
SessionID|CourseCode|Day|Start|End|Location|OpenTimestamp|DurationMinutes|EligibleStudentIDs

5.Attendance records:
StudentID|SessionID|Status|Timestamp|CaptureMethod

6.Attendance corrections:
StudentID|SessionID|LecturerID|CorrectedStatus|Reason|Timestamp

7.File Replay Demonstration
data/replay.txt is provided to demonstrate both valid and invalid attendance events. It contains a valid student ID, a 
malformed line, a non-enrolled student, and a duplicate student event so that exception paths can be demonstrated.

-------------
Design Notes
-------------
The system uses three major polymorphic hierarchies:
- Person -> Student / Lecturer / Administrator
- Course -> LectureCourse / LabCourse / ProjectCourse
- AttendanceCapture -> RotatingCodeCapture / FileReplayCapture

AttendanceSession owns its selected AttendanceCapture object and implements explicit resource-management semantics. Student owns its enrolment records, Course owns its time slots, while course/student/lecturer relationships are restored by identifiers during loading.
Known Limitations
- The application is console-based and stores data in local text files.
- Passwords are stored as plain text because authentication security is outside the project scope.
- The program is intended for a single-process demonstration and does not provide concurrent file access.
- Time slots use whole-hour integer values rather than minute-level scheduling.
- Course grading strategies are implemented in the domain model; full assessment-entry workflow is not exposed through the console menus.


-----------------------------------------------------------------------------------------------------------------------------
AI Usage
AI-assisted tools(ChatGPT,CLAUDE,GEMINI) were used during development for explanation of C++/OOP concepts, debugging support, review of compiler/linker errors, test planning, and suggestions for implementation improvements. The group reviewed, integrated, tested, and is responsible for the submitted implementation. The group reviewed, integrated and tested the final implementation and is responsible for understanding the submitted code.
-----------------------------------------------------------------------------------------------------------------------------