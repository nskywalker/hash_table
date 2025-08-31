//
// Created by googl on 31.08.2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <ranges>

template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
class HashTable {
    struct Node {
        Key key;
        Value value;
    };
    using ListNode = std::list<Node>;
    using HashRows = std::vector<ListNode>;
    HashRows rows;
    std::hash<Key> hasher;
    size_t size = 0;
    void rehash();
public:
    HashTable();
    bool insert(Key key, Value value);
    bool remove(const Key& key);
    Value* find(const Key& key);
};


template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
void HashTable<Key, Value>::rehash()
{
    HashRows newRows(rows.capacity() * 2, ListNode{});
    while (!rows.empty()){
        auto& row = rows.back();
        while (!row.empty()){
            auto [key, value] = row.front();
            auto index = hasher(key) % newRows.capacity();
            newRows[index].emplace_back(std::move(key), std::move(value));
            row.pop_front();
        }
        rows.pop_back();
    }
    rows = std::move(newRows);
}

template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
HashTable<Key, Value>::HashTable()
{
    rows.resize(10);
}

template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
bool HashTable<Key, Value>::insert(Key key, Value value)
{
    auto index = hasher(key) % rows.capacity();
    auto& row = rows[index];
    auto it = std::ranges::find(row, key, &Node::key);
    if (it != row.end()){
        return false;
    }
    row.emplace_back(std::move(key), std::move(value));
    if (++size >= rows.capacity() / 2){
        rehash();
    }
    return true;
}

template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
bool HashTable<Key, Value>::remove(const Key& key)
{
    auto index = hasher(key) % rows.capacity();
    auto& row = rows[index];
    auto it = std::ranges::find(row, key, &Node::key);
    if (it != row.end()){
        row.erase(it);
        --size;
        return true;
    }
    return false;
}

template <typename Key, typename Value>
requires std::move_constructible<Key> && std::move_constructible<Value>
Value* HashTable<Key, Value>::find(const Key& key)
{
    auto index = hasher(key) % rows.capacity();
    auto& row = rows[index];
    auto it = std::ranges::find(row, key, &Node::key);
    return it == row.end() ? nullptr : &(it->value);
}
#endif //HASHTABLE_H
