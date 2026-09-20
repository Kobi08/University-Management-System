#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <string>
#include <list>

#include "Person.h"
using namespace std;

class Course;

class Lecturer : public Person
{

private:
    list<Course*> assignedCourse;
    

public:
    Lecturer(const string& name,
             const string& password);

    Lecturer(const string& name,
         const string& password,
         const string& id);

    void showMenu() override;

    void viewEnrolment(Course& course) const;
    void openAttendance(Course& course);

    
    void assignCourse(Course& course);
    list<Course*> getAssignedCourses() const;

    friend ostream& operator<<(ostream& os,
                                    const Lecturer& lecturer);

    template<typename T>
    friend class Repository;

    ~Lecturer() override = default;
};

#endif