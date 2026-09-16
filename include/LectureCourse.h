#pragma once

#include "Course.h"

class LectureCourse : public Course {
public:
    LectureCourse(const string& code, const string& title, int credit, int capacity,
                  Lecturer& asignlecturer,
                  const list<string>& prerequisites = {});

    double calculategrade(const AssessmentMarks& marks) const override;
};