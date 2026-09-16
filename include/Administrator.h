#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <list>
#include "Person.h"
#include "Lecturer.h"

using namespace std;

class Administrator : public Person
{
public:
    Administrator(const string& name, const string& password);

    void showMenu() override;
    void createuser(const string& name, const string& id, const string& role);
    void updateuser(const string& id, const string& newname, const string& newpass);
    bool removeuser(const string& id);

    bool createcourse(const string& code, const string& title, int credits, int capacity,
                      Lecturer& assignedlecturer, const list<string>& prerequisites,
                      const string& coursetype);

    void editcourse(const string& code, const string& newcode, const string& newtitle,
                    int newcredits, int newcapacity, Lecturer& newassignedlecturer,
                    const list<string>& newprerequisites, const string& newcoursetype);

    bool removecourse(const string& code);

    void generateenrolmentreport() const;
};

#endif