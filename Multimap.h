#pragma once
#include "RedBlackTree.h"
#include <iostream>

template<typename Key, typename Value>
class Multimap {
public:
    using ValueType = std::list<Value>;
    Multimap() : rbTree(), size(0) {}
    ~Multimap() {}

    void insert(const Key& key,const Value& value) {
        ValueType* ans = rbTree.at(key);
        if (ans) {
            ans->push_back(value);
        } else {
            ValueType values;
            values.push_back(value);
            rbTree.insert(key, values);
        }
        size++;
    }

    void remove(const Key& key) {
        ValueType* ans = rbTree.at(key);
        if (ans) {
            size -= ans->size();
            rbTree.remove(key);
        }
    }

    void remove(const Key& key, const Value& value) {
        ValueType* ans = rbTree.at(key);
        if (ans) {
            ans->remove(value);
            size--;
        }

        if (ans->empty()) {
            rbTree.remove(key);
        }
    }

    ValueType* at(const Key& key) {
        return rbTree.at(key);
    }

    size_t getSize(){
        return size;
    }

    bool empty() {
        return rbTree.size() == 0;
    }

private:
    RedBlackTree<Key, Value> rbTree;
    size_t size;
};