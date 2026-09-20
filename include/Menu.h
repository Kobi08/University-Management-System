#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include <vector>

#include "Person.h"
#include "Course.h"
#include "AttendanceRegister.h"

class Student;
class Lecturer;
class Administrator;

class Menu
{
private:
    friend class Administrator;
    friend class Student;
    friend class Lecturer;
    void loadUsers();
    void loadCourses();
    void loadEnrolments();
    void loadAttendance();

    // Own the application's users and courses.
    std::vector<std::unique_ptr<Person>> users;
    std::vector<std::unique_ptr<Course>> courses;

    AttendanceRegister attendance;

    std::string dataPath;

    // Refers to the logged-in user; does not own that user.
    Person* current = nullptr;

    bool stop = false;
    bool dirty = false;

    // Input helpers.
    static std::string ask(const std::string& prompt);

    static int number(const std::string& prompt,
                      int low,
                      int high);

    // Save after a successful change.
    void saveAction();

    // Display available data.
    void listCourses() const;
    void listUsers() const;

    // Convert between application objects and saved text rows.
    std::vector<std::string> rows() const;

    void loadRows(const std::vector<std::string>& savedRows);

    // Application-state helpers.
    void clear();
    void rebuildLecturerCourses();

public:
    explicit Menu(
        const std::string& dataPath = "data/system.txt"
    );

    ~Menu();

    void run();
    void showloginmenu();

    // Separate handlers for the three existing user roles.
   
    // Find existing objects by their identifiers.
    Person* findUser(const std::string& id) const;
    Course* findCourse(const std::string& code) const;

    void save() const;
    void load();

    void createDemo();

    // Check whether deleting an object would break existing links.
    bool userReferenced(const Person* user) const;
    bool courseReferenced(const Course* course) const;
};

#endif