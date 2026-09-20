#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "Exceptions.h"

template<typename T>
class Repository
{
private:
    std::string filepath;

public:
    explicit Repository(const std::string& path)
        : filepath(path)
    {
    }

    std::vector<T> load() const
{
    std::ifstream input(filepath);

    if (!input.is_open())
    {
        throw FileNotFoundException(
            "Cannot open data file: " + filepath
        );
    }

    std::vector<T> items;
    std::string line;

    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }

        T item{};

        if constexpr (std::is_same_v<T, std::string>)
        {
            // For strings, keep the complete line exactly as stored.
            item = line;
        }
        else
        {
            std::istringstream row(line);

            row >> item;

            if (!row)
            {
                throw CorruptDataException(
                    "Invalid data in: " + filepath
                );
            }

            row >> std::ws;

            if (!row.eof())
            {
                throw CorruptDataException(
                    "Unexpected extra data in: " + filepath
                );
            }
        }

        items.push_back(item);
    }

    if (input.bad())
    {
        throw PersistenceException(
            "Failed to read: " + filepath
        );
    }

    return items;
}

    void save(const std::vector<T>& items) const
    {
        namespace fs = std::filesystem;

        const fs::path target(filepath);
        const fs::path temporary(filepath + ".tmp");
        const fs::path backup(filepath + ".bak");

        try
        {
            if (target.has_parent_path())
            {
                fs::create_directories(target.parent_path());
            }

            std::ofstream output(temporary, std::ios::trunc);

            if (!output.is_open())
            {
                throw PersistenceException(
                    "Cannot create temporary file: " +
                    temporary.string()
                );
            }

            for (const T& item : items)
            {
         if constexpr (std::is_same_v<T, std::string>)
        {
            output << item;
        }
        else
        {
            output << item;
        }

                output << '\n';
            }

            output.flush();

            if (!output)
            {
                throw PersistenceException(
                    "Writing failed. Previous data was retained."
                );
            }

            output.close();

            if (!output)
            {
                throw PersistenceException(
                    "Closing the file failed. Previous data was retained."
                );
            }

            const bool hadPreviousFile = fs::exists(target);

            if (hadPreviousFile)
            {
                if (fs::exists(backup))
                {
                    fs::remove(backup);
                }

                fs::rename(target, backup);
            }

            try
            {
                fs::rename(temporary, target);
            }
            catch (...)
            {
                if (hadPreviousFile)
                {
                    fs::rename(backup, target);
                }

                throw;
            }
        }
        catch (const fs::filesystem_error& error)
        {
            throw PersistenceException(
                std::string("File operation failed: ") +
                error.what()
            );
        }
    }

    void add(const T& item) const
    {
        std::vector<T> items = load();
        items.push_back(item);
        save(items);
    }

    void remove(const T& item) const
    {
        std::vector<T> items = load();

        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (*it == item)
            {
                items.erase(it);
                save(items);
                return;
            }
        }
    }
};

#endif