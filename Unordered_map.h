#pragma once
#include "HashTable.h"
#include <iostream>

template<typename Key, typename Value>
class Unordered_map {
public:
    Unordered_map() : hashtable() {}
    ~Unordered_map();

    bool empty() {
        return hashtable.size() == 0;
    }

    size_t size() {
        return hashtable.size();
    }

    void clear() {
        hashtable.clear();
    }

    void insert(const Key& key, const Value& value) {
        hashtable.insert(key, value);
    }

    void erase(const Key& key) {
        hashtable.erase(key);
    }

    bool find(const Key& key) {
        return hashtable.find(key) != nullptr;
    }

    Value& operator[](const Key& key) {
        Value* ans = hashtable.find(key);
        if (ans) {
            return *ans;
        }
        hashtable.insert(key);
        ans = hashtable.find(key);
        return *ans;
    }

private:
    HashTable<Key, Value> hashtable;
};