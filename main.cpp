#include <exception>
#include <iostream>

#include "Menu.h"

int main()
{
    try
    {
        Menu app;
        app.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << "Fatal error: "
                  << error.what()
                  << '\n';

        return 1;
    }

    return 0;
}