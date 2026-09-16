#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <string>
#include <list>
#include "Person.h"
#include "Course.h"
#include "TimeSlot.h"

using namespace std;

class Lecturer : public Person
{
private:
    list<Course*> assignedcourse;

public:
    Lecturer(const string& name, const string& password);

    void showMenu() override;
    void viewenrolment(Course& course);
    void openattendancesession(const TimeSlot& slot);
    void closeattendancesession();
};

#endif
