#include "LabCourse.h"
#include "AssessmentMarks.h"
#include <stdexcept>

LabCourse::LabCourse(const string& code, const string& title, int credit, int capacity,
                     Lecturer& asignlecturer,
                     const list<string>& prerequisites)
    : Course(code, title, credit, capacity, asignlecturer, prerequisites) {}

double LabCourse::calculategrade(const AssessmentMarks& marks) const {
    const list<double> practicalMarks = marks.getPracticalMarks();

    if (practicalMarks.empty()) {
        throw invalid_argument("Practical marks have not been entered");
    }

    double total = 0;
    for (double mark : practicalMarks) {
        total += mark;
    }

    return total / practicalMarks.size();
}
