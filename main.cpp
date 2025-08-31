#include <assert.h>
#include <print>
#include "HashTable.h"
#include <string>

int main()
{
    HashTable<std::string, std::string> table;
    table.insert("cat", "orange");
    table.insert("dog", "brown");
    table.insert("cow", "white");
    table.insert("fox", "red");
    table.insert("owl", "gray");
    table.insert("pig", "pink");

    assert(table.find("cat") != nullptr);
    assert(table.find("dog") != nullptr);
    assert(table.find("cow") != nullptr);
    assert(table.find("fox") != nullptr);
    assert(table.find("pig") != nullptr);
    assert(table.find("owl") != nullptr);

    assert(table.find("lion") == nullptr);
    assert(table.find("chicken") == nullptr);
    assert(table.find("horse") == nullptr);

    assert(table.remove("cat"));
    assert(table.remove("dog"));
    assert(table.remove("fox"));
    assert(table.remove("pig"));

    assert(!table.remove("lion"));
    assert(!table.remove("chicken"));

    return 0;
}