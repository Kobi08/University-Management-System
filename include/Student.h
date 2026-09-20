#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Person.h"
#include "Timetable.h"

using namespace std;

class Course;
class Enrolment;
class Administrator;


class Student : public Person
{
private:
    Timetable timetable;
        friend class Menu;
        friend class Administrator;

    std::vector<std::unique_ptr<Enrolment>> enrolments;

public:
    Student(const string& name,
            const string& password);

    Student(const string& name,
        const string& password,
        const string& id);

    void showMenu() override;

    void enrollCourse(Course& course);
    void dropCourse(Course& course);

    bool hasCompleted(const string& courseCode) const;
    bool isEnrolled(const Course& course) const;

    void viewTimetable() const;

    friend ostream& operator<<(ostream& os, const Student& student);

        ~Student() override;
};

#endif