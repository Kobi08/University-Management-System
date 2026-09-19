#pragma once

#include <list>

using namespace std;

class AssessmentMarks
{
private:
    double caScore;
    double examScore;
    list<double> practicalMarks;
    double submissionScore;

public:
    AssessmentMarks();

    void setCAScore(double score);
    void setExamScore(double score);
    void setPracticalMarks(const list<double>& marks);
    void setSubmissionScore(double score);

    double getCAScore() const;
    double getExamScore() const;
    list<double> getPracticalMarks() const;
    double getSubmissionScore() const;
};