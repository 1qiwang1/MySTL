#pragma once
#include <iostream>
#include "RedBlackTree.h"


template <typename Key>
class Set {
public:
    Set() : rbTree() {}
    void insert(const Key& key) { rbTree.insert(key, key); }

    void erase(const Key& key) { rbTree.remove(key); }

    size_t size() { return rbTree.getSize(); }

    bool empty() { return rbTree.empty(); }

    bool contains(const Key& key) { return rbTree.at(key) != nullptr; }

private:
    RedBlackTree<Key, Key> rbTree;
};