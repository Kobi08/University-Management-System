#include "Person.h"

#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

int Person::nextId = 1;

string Person::generateId()
{
    stringstream ss;

    ss << setw(3)
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

Person::Person(const string& name,
               const string& password,
               const string& id)
    : name(name),
      id(id),
      password(password)
{
    int loadedId = stoi(id);

    nextId = max(nextId, loadedId + 1);
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