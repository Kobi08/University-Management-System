#include "ProjectCourse.h"
#include "AssessmentMarks.h"

#include <stdexcept>

ProjectCourse::ProjectCourse(const string& code,
                             const string& title,
                             int credit,
                             int capacity,
                             Lecturer& asignlecturer,
                             const list<string>& prerequisites)
    : Course(code,
             title,
             credit,
             capacity,
             asignlecturer,
             prerequisites)
{
}

double ProjectCourse::calculateGrade(const AssessmentMarks& marks) const
{
    const double submissionScore = marks.getSubmissionScore();

    if (submissionScore == -1)
    {
        throw invalid_argument("Submission score has not been entered");
    }

    return submissionScore;
}

string ProjectCourse::getCourseType() const
{
    return "Project";
}