#include "RedBlackTree.h"
#include <iostream>
#include <utility>

template<typename Key, typename Value>
class Map {
public:
    Map() : rbTree() {}
    ~Map(){}

    void insert(const Key& key, const Value& value) {
        rbTree.insert(key, value);
    }

    void erase(const Key& key) {
        rbTree.remove(key);
    }

    size_t size() {
        return rbTree.getSize();
    }

    bool empty() {
        return rbTree.empty();
    }

    bool contains(const Key& key) {
        return rbTree.at(key) != nullptr;
    }

    Value& at(const Key& key) {
        Value* foundVal = rbTree.at(key);
        if (foundVal) {
            return *foundVal;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    Value& operator[](const Key& key) {
        Value* foundVal = rbTree.at(key);
        if (foundVal) {
            return *foundVal;
        } else {
            Value defaultValue;
            rbTree.insert(key, defaultValue);
            return *rbTree.at(key);
        }
    }


private:
    RedBlackTree<Key, Value> rbTree;
};


