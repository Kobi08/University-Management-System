#include "Menu.h"
#include "Exceptions.h"
#include "Lecturer.h"

#include <iostream>
#include <sstream>

Menu::Menu(const std::string& path)
    : dataPath(path)
{
}

std::string Menu::ask(const std::string& prompt)
{
    std::cout << prompt;

    std::string value;

    if (!std::getline(std::cin, value))
    {
        throw Exception("Input closed.");
    }

    return value;
}

int Menu::number(const std::string& prompt,
                 int low,
                 int high)
{
    const std::string text = ask(prompt);

    std::istringstream input(text);
    int value;

    if (!(input >> value))
    {
        throw Exception("Enter a whole number.");
    }

    // Allow trailing spaces, but reject extra text.
    input >> std::ws;

    if (!input.eof())
    {
        throw Exception(
            "Enter a whole number without extra characters."
        );
    }

    if (value < low || value > high)
    {
        throw Exception(
            "Enter a number between " +
            std::to_string(low) + " and " +
            std::to_string(high) + "."
        );
    }

    return value;
}

Person* Menu::findUser(const std::string& id) const
{
    for (const auto& user : users)
    {
        if (user->getId() == id)
        {
            return user.get();
        }
    }

    return nullptr;
}

Course* Menu::findCourse(const std::string& code) const
{
    for (const auto& course : courses)
    {
        if (course->getCode() == code)
        {
            return course.get();
        }
    }

    return nullptr;
}

void Menu::listUsers() const
{
    std::cout << "\n===== USERS =====\n";

    if (users.empty())
    {
        std::cout << "No users available.\n";
        return;
    }

    for (const auto& user : users)
    {
        std::cout << "ID: " << user->getId()
                  << " | Name: " << user->getName()
                  << '\n';
    }
}

void Menu::listCourses() const
{
    std::cout << "\n===== COURSES =====\n";

    if (courses.empty())
    {
        std::cout << "No courses available.\n";
        return;
    }

    for (const auto& course : courses)
    {
        std::cout << *course << '\n';

        std::cout << "Type: "
                  << course->getCourseType()
                  << '\n';

        const Lecturer* lecturer = course->getLecturer();

        if (lecturer != nullptr)
        {
            std::cout << "Lecturer: "
                      << lecturer->getId()
                      << " | "
                      << lecturer->getName()
                      << '\n';
        }

        for (const TimeSlot& slot : course->getTimeSlots())
        {
            std::cout << "  " << slot << '\n';
        }

        std::cout << '\n';
    }
}

