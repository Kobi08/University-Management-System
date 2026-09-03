This is the oop project where we built console based university management system.


------------------------------
THIS IS THE DRAFT PLAN
------------------------------

UniversityManagementSystem/
│
├── include/
│   ├── Person.h
│   ├── Student.h
│   ├── Lecturer.h
│   ├── Administrator.h
│   │
│   ├── Course.h
│   ├── LectureCourse.h
│   ├── LabCourse.h
│   ├── ProjectCourse.h
│   │
│   ├── Enrolment.h
│   ├── TimeSlot.h
│   ├── Timetable.h
│   │
│   ├── AttendanceCapture.h
│   ├── RotatingCodeCapture.h
│   ├── FileReplayCapture.h
│   ├── AttendanceSession.h
│   ├── AttendanceRecord.h
│   ├── CorrectionRecord.h
│   ├── AttendanceRegister.h
│   │
│   ├── Repository.h
│   └── Exceptions.h
│
├── src/
│   ├── Person.cpp
│   ├── Student.cpp
│   ├── Lecturer.cpp
│   ├── Administrator.cpp
│   ├── Course.cpp
│   ├── LectureCourse.cpp
│   ├── LabCourse.cpp
│   ├── ProjectCourse.cpp
│   ├── Enrolment.cpp
│   ├── TimeSlot.cpp
│   ├── Timetable.cpp
│   ├── AttendanceSession.cpp
│   ├── AttendanceRecord.cpp
│   ├── CorrectionRecord.cpp
│   ├── AttendanceRegister.cpp
│   ├── RotatingCodeCapture.cpp
│   └── FileReplayCapture.cpp
│
├── data/
│   ├── students.txt
│   ├── lecturers.txt
│   ├── courses.txt
│   ├── enrolments.txt
│   └── attendance.txt
│
├── docs/
│   ├── UML.png
│   └── change-log.md
│
├── main.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore