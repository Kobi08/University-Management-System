cmake_minimum_required(VERSION 3.10)

project(UniversityManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)

include_directories(include)

add_executable(UniversityManagementSystem
    main.cpp

    src/TimeSlot.cpp
    src/Person.cpp
    src/Timetable.cpp
    src/Course.cpp
    src/AssessmentMarks.cpp
    src/LectureCourse.cpp
    src/LabCourse.cpp
    src/ProjectCourse.cpp
)
