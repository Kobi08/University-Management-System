#pragma once

#include "Course.h"

class LabCourse : public Course
{
public:
    LabCourse(const string& code,
              const string& title,
              int credit,
              int capacity,
              Lecturer& asignlecturer,
              const list<string>& prerequisites = {});

    double calculateGrade(const AssessmentMarks& marks) const override;

    string getCourseType() const override;
};