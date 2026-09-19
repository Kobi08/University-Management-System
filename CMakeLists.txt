cmake_minimum_required(VERSION 3.10)

project(UniversityManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)

include_directories(include)

add_executable(UniversityManagementSystem

    main.cpp

    src/TimeSlot.cpp
    src/Timetable.cpp
    src/AttendanceSession.cpp
    src/RotatingCodeCapture.cpp
    src/AttendanceRecord.cpp
    src/CorrectionRecord.cpp
    src/AttendanceRegister.cpp

)
      main.cpp
    src/Person.cpp
    src/Student.cpp
    src/Lecturer.cpp
    src/Administrator.cpp
    src/Course.cpp
    src/LectureCourse.cpp
    src/LabCourse.cpp
    src/ProjectCourse.cpp
    src/AssessmentMarks.cpp
    src/Enrolment.cpp
    

)
