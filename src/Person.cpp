#include "Person.h"

#include <iomanip>
#include <sstream>

using namespace std;

int Person::nextId = 1;

string Person::generateId()
{
    stringstream ss;

    ss << "U"
       << setw(3)
       << setfill('0')
       << nextId++;

    return ss.str();
}

Person::Person(const string& name,
               const string& password)
    : name(name),
      id(generateId()),
      password(password)
{
}

bool Person::login(const string& enteredPassword) const
{
    return enteredPassword == password;
}

void Person::logout()
{
    // Logout behavior will be handled by the authentication/menu system.
}

string Person::getName() const
{
    return name;
}

string Person::getId() const
{
    return id;
}