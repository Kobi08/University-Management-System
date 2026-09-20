#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Menu;
class Administrator;

class Person
{
private:
    friend class Menu;
    friend class Administrator;

    string name;
    string id;
    string password;

    static int nextId;
    static string generateId();

protected:
    // Refers to the application; Person does not own it.
    Menu* application = nullptr;

    Person(const string& name,
           const string& password);

public:
    void setApplication(Menu* app)
    {
        application = app;
    }

    bool login(const string& enteredPassword) const;

    void logout();

    string getName() const;
    string getId() const;

    virtual void showMenu() = 0;

    virtual ~Person() = default;
};

#endif