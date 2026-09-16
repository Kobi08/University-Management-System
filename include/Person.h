#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
private:
    string name;
    string id;
    string password;

    static int nextId;

    static string generateId();

protected:
    Person(const string& name,
           const string& password);

public:
    bool login(const string& enteredPassword) const;
    void logout();

    string getName() const;
    string getId() const;

    virtual void showMenu() = 0;

    virtual ~Person() = default;
};

#endif