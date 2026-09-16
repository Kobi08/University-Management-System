#include "LectureCourse.h"
#include "AssessmentMarks.h"
#include <stdexcept>

LectureCourse::LectureCourse(const string& code, const string& title, int credit, int capacity,
                             Lecturer& asignlecturer,
                             const list<string>& prerequisites)
    : Course(code, title, credit, capacity, asignlecturer, prerequisites) {}

double LectureCourse::calculategrade(const AssessmentMarks& marks) const {
    if (marks.getCAScore() < 0 || marks.getExamScore() < 0) {
        throw invalid_argument("CA score or exam score has not been entered");
    }

    return (marks.getCAScore() * 0.40) + (marks.getExamScore() * 0.60);
}