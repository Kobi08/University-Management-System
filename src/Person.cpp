#include "Person.h"

#include <iomanip>
#include <sstream>
#include <algorithm>

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

Person::Person(const string& name,
               const string& password,
               const string& id)
    : name(name),
      id(id),
      password(password)
{
    std::string numericPart = id;

    if (!numericPart.empty() &&
        numericPart.front() == 'U')
    {
        numericPart.erase(0, 1);
    }

    if (!numericPart.empty())
    {
        int loadedId = std::stoi(numericPart);

        nextId = std::max(
            nextId,
            loadedId + 1
        );
    }
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