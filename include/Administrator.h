#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>
#include <string>
#include <list>

#include "Person.h"

using namespace std;

class Lecturer;
class Student;

class Administrator : public Person
{

private:
    list<Student>* studentUsers = nullptr;
    list<Lecturer>* lecturerUsers = nullptr;
    list<Administrator>* administratorUsers = nullptr;
public:
    Administrator(const string& name,
                  const string& password);

    Administrator(const string& name,
              const string& password,
              const string& id);

    void showMenu() override;

    void createUser(
                    const string& name,
                    const string& password,
                    const string& role);

    void updateUser(const string& id,
                    const string& newName,
                    const string& newPass);

    void connectUsers(
    list<Student>& students,
    list<Lecturer>& lecturers,
    list<Administrator>& administrators);

    bool removeUser(const string& id);

    bool createCourse(const string& code,
                      const string& title,
                      int credits,
                      int capacity,
                      Lecturer& assignedLecturer,
                      const list<string>& prerequisites,
                      const string& courseType);

    void editCourse(const string& code,
                    const string& newCode,
                    const string& newTitle,
                    int newCredits,
                    int newCapacity,
                    Lecturer& newAssignedLecturer,
                    const list<string>& newPrerequisites,
                    const string& newCourseType);

    string removeCourse(const string& code);

    void generateEnrolmentReport();

    friend ostream& operator<<(ostream& os,
                               const Administrator& administrator);

    ~Administrator() override = default;
};

#endif