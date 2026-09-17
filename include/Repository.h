#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <fstream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

template<typename T>
class Repository
{
private:
    string filepath;

public:
    Repository(const string& filepath);

    void save(const list<T>& items) const;

    list<T> load() const;

    void add(const T& item);

    void remove(const T& item);
};

template<typename T>
Repository<T>::Repository(const string& filepath)
    : filepath(filepath)
{
}

template<typename T>
void Repository<T>::save(const list<T>& items) const
{
    ofstream file(filepath);

    for (const T& item : items)
    {
        file << item << endl;
    }
}

template<typename T>
list<T> Repository<T>::load() const
{
    list<T> items;

    ifstream file(filepath);

    // Loading logic will be completed
    // once serialization format is finalized.

    return items;
}

template<typename T>
void Repository<T>::add(const T& item)
{
    list<T> items = load();

    items.push_back(item);

    save(items);
}

template<typename T>
void Repository<T>::remove(const T& item)
{
    list<T> items = load();

    items.remove(item);

    save(items);
}

#endif