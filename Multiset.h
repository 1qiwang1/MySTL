#pragma once
#include <iostream>
#include "RedBlackTree.h"


template<typename Key>
class Multiset {
public:
    Multiset() : sz(0) {}
    ~Multiset() {}

    void insert(const Key& key) {
        auto count = rbTree.at(key);
        if (count != nullptr) {
            (*count)++;
            sz++;
            return;
        }
        rbTree.insert(key, 1);
        sz++;
    }

    void erase(const Key& key) {
        auto count = rbTree.at(key);
        if (count == nullptr) {
            return;
        }
        (*count)--;
        sz--;
        if ((*count) == 0) {
            rbTree.remove(key);
        }
    }

    size_t size() {
        return sz;
    }

    size_t count(const Key& key) {
        auto num = rbTree.at(key);
        if (num != nullptr) {
            return (*num);
        }
        return 0;
    }

    void clear() {
        sz = 0;
        rbTree.clear();
    }

    bool empty() const {
        return sz == 0;
    }

private:
    RedBlackTree<Key, size_t> rbTree;
    size_t sz;
};

