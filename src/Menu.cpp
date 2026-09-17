#include "Menu.h"

#include <iostream>

using namespace std;

void Menu::showLoginMenu()
{
    cout << "\n================================\n";
    cout << " University Management System\n";
    cout << "================================\n";

    cout << "1. Login\n";
    cout << "0. Exit\n";
}

void Menu::run()
{
    int choice;

    do
    {
        showLoginMenu();

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nLogin system will be connected next.\n";
            break;

        case 0:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 0);
}