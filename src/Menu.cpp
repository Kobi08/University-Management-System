#include "Menu.h"
#include "Repository.h"

#include <iostream>
#include <stdexcept>
#include <unordered_set>

void Menu::loadUsers()
{
    Repository<Student> studentRepository("data/students.txt");

    Repository<Lecturer> lecturerRepository("data/lecturers.txt");

    Repository<Administrator> administratorRepository(
        "data/administrators.txt"
    );

    // Load into temporary collections first.
    auto loadedStudents = studentRepository.load();
    auto loadedLecturers = lecturerRepository.load();
    auto loadedAdministrators = administratorRepository.load();

    // IDs must be unique across all three roles.
    std::unordered_set<std::string> usedIds;

    auto validateIds = [&usedIds](const auto& users)
    {
        for (const auto& user : users)
        {
            if (!usedIds.insert(user.getId()).second)
            {
                throw std::runtime_error(
                    "Duplicate user ID: " + user.getId()
                );
            }
        }
    };

    validateIds(loadedStudents);
    validateIds(loadedLecturers);
    validateIds(loadedAdministrators);

    // Store the validated objects for the application's lifetime.
    students.swap(loadedStudents);
    lecturers.swap(loadedLecturers);
    administrators.swap(loadedAdministrators);

    for (Administrator& administrator : administrators)
{
    administrator.connectUsers(
        students,
        lecturers,
        administrators
    );
}
}

Person* Menu::findUser(const std::string& id)
{
    for (Student& student : students)
    {
        if (student.getId() == id)
        {
            return &student;
        }
    }

    for (Lecturer& lecturer : lecturers)
    {
        if (lecturer.getId() == id)
        {
            return &lecturer;
        }
    }

    for (Administrator& administrator : administrators)
    {
        if (administrator.getId() == id)
        {
            return &administrator;
        }
    }

    return nullptr;
}

void Menu::showLoginMenu()
{
    std::cout << "\n=================================\n";
    std::cout << " University Management System\n";
    std::cout << "=================================\n";
    std::cout << "Enter 0 as your ID to exit.\n";
}

void Menu::run()
{
    loadUsers();

    while (true)
    {
        showLoginMenu();

        std::string id;
        std::string password;

        std::cout << "ID: ";

        if (!(std::cin >> id))
        {
            return;
        }

        if (id == "0")
        {
            std::cout << "Application closed.\n";
            return;
        }

        std::cout << "Password: ";

        if (!(std::cin >> password))
        {
            return;
        }

        Person* currentUser = findUser(id);

        if (currentUser == nullptr ||
            !currentUser->login(password))
        {
            std::cout << "Invalid ID or password.\n";
            continue;
        }

        std::cout << "\nWelcome, "
                  << currentUser->getName()
                  << "!\n";

        // Runtime polymorphism chooses the correct role menu.
        currentUser->showMenu();

        // When showMenu() returns after logout,
        // the loop displays the login screen again.
    }
}