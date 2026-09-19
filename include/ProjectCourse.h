#pragma once

#include "Course.h"

class ProjectCourse : public Course
{
public:
    ProjectCourse(const string& code,
                  const string& title,
                  int credit,
                  int capacity,
                  Lecturer& asignlecturer,
                  const list<string>& prerequisites = {});

    double calculateGrade(const AssessmentMarks& marks) const override;

    string getCourseType() const override;
};