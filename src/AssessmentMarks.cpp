#include "AssessmentMarks.h"

#include <stdexcept>

AssessmentMarks::AssessmentMarks()
    : caScore(-1),
      examScore(-1),
      practicalMarks(),
      submissionScore(-1)
{
}

void AssessmentMarks::setCAScore(double score)
{
    if (score < 0 || score > 100)
    {
        throw invalid_argument("Invalid CA score");
    }

    caScore = score;
}

void AssessmentMarks::setExamScore(double score)
{
    if (score < 0 || score > 100)
    {
        throw invalid_argument("Invalid exam score");
    }

    examScore = score;
}

void AssessmentMarks::setPracticalMarks(const list<double>& marks)
{
    for (double mark : marks)
    {
        if (mark < 0 || mark > 100)
        {
            throw invalid_argument("Invalid practical mark");
        }
    }

    practicalMarks = marks;
}

void AssessmentMarks::setSubmissionScore(double score)
{
    if (score < 0 || score > 100)
    {
        throw invalid_argument("Invalid submission score");
    }

    submissionScore = score;
}

double AssessmentMarks::getCAScore() const
{
    return caScore;
}

double AssessmentMarks::getExamScore() const
{
    return examScore;
}

list<double> AssessmentMarks::getPracticalMarks() const
{
    return practicalMarks;
}

double AssessmentMarks::getSubmissionScore() const
{
    return submissionScore;
}