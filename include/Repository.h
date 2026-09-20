#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdexcept>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "Enrolment.h"
#include "Course.h"

using namespace std;

// Generic Template Class Definition
template<typename T>
class Repository
{
private:
    string filepath;

public:
    Repository(const string& filepath) : filepath(filepath) {}

    void save(const list<T>& items) const
    {
        ofstream file(filepath);
        if (!file.is_open())
        {
            throw runtime_error("Unable to open file: " + filepath);
        }
        for (const T& item : items)
        {
            file << item << endl;
        }
    }

    list<T> load() const
    {
        list<T> items;
        return items;
    }

    void add(const T& item)
    {
        list<T> items = load();
        items.push_back(item);
        save(items);
    }

    void remove(const T& item)
    {
        list<T> items = load();
        items.remove(item);
        save(items);
    }
};

// Specialized load for Student
template<>
inline list<Student> Repository<Student>::load() const
{
    list<Student> students;
    ifstream file(filepath);

    if (!file.is_open())
    {
        throw runtime_error("Unable to open file: " + filepath);
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, password;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');

        students.emplace_back(name, password, id);
    }

    return students;
}

// Specialized load for Lecturer
template<>
inline list<Lecturer> Repository<Lecturer>::load() const
{
    list<Lecturer> lecturers;
    ifstream file(filepath);

    if (!file.is_open())
    {
        throw runtime_error("Unable to open file: " + filepath);
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, password;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');

        lecturers.emplace_back(name, password, id);
    }

    return lecturers;
}

// Specialized load for Administrator
template<>
inline list<Administrator> Repository<Administrator>::load() const
{
    list<Administrator> administrators;
    ifstream file(filepath);

    if (!file.is_open())
    {
        throw runtime_error("Unable to open file: " + filepath);
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, password;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');

        administrators.emplace_back(name, password, id);
    }

    return administrators;
}

// Explicit Class Template Specialization for Enrolment
// Handles reconnecting pointer references during load
template<>
class Repository<Enrolment>
{
private:
    string filepath;

public:
    Repository(const string& filepath) : filepath(filepath) {}

    void save(const list<Enrolment>& items) const
    {
        ofstream file(filepath);
        if (!file.is_open())
        {
            throw runtime_error("Unable to open file: " + filepath);
        }
        for (const Enrolment& item : items)
        {
            file << item << endl;
        }
    }

    list<Enrolment> load(list<Student>& students, const list<Course*>& courses) const
    {
        list<Enrolment> enrolments;
        ifstream file(filepath);

        if (!file.is_open())
        {
            throw runtime_error("Unable to open file: " + filepath);
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;

            stringstream ss(line);
            string studentId, courseCode, status, dateEnrolled, gradeStr;

            getline(ss, studentId, '|');
            getline(ss, courseCode, '|');
            getline(ss, status, '|');
            getline(ss, dateEnrolled, '|');
            getline(ss, gradeStr, '|');

            double grade = gradeStr.empty() ? 0.0 : stod(gradeStr);

            // Find matching active Student pointer
            Student* targetStudent = nullptr;
            for (auto& s : students)
            {
                if (s.getId() == studentId)
                {
                    targetStudent = &s;
                    break;
                }
            }

            // Find matching active Course pointer
            Course* targetCourse = nullptr;
            for (auto* c : courses)
            {
                if (c->getcode() == courseCode)
                {
                    targetCourse = c;
                    break;
                }
            }

            if (targetStudent && targetCourse)
            {
                enrolments.emplace_back(*targetStudent, *targetCourse, status, dateEnrolled, grade);
            }
        }

        return enrolments;
    }
};

#endif