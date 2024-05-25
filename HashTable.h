#pragma once
#include<iostream>
#include<functional>
#include <list>
#include <vector>


template<typename Key, typename Value, typename Hash = hash<Key>>
class HashTable {
    class HashNode {
    public:
        Key key;
        Value value;

        explicit HashNode(const Key& key) : key(key), value(value) {}

        HashNode(const Key& key, const Value& value) : key(key), value(value) {}

        bool operator==(const HashNode& other) const { return key == other.key; }

        bool operator!=(const HashNode& other) const { return key != other.key; }

        bool operator<(const HashNode& other) const { return key < other.key; }

        bool operator>(const HashNode& other) const { return key > other.key; }

        bool operator==(const Key& key_) const { return key == key_; }

        void print() const {
            cout << key << " " << value << " ";
        }
    };

private:
    // 定义桶的类型为存储键的链表
    using Bucket = list<HashNode>;

    // 存储所有桶的动态数组
    vector<Bucket> buckets;

    // 哈希函数对象
    Hash hashFunction;

    // 哈希表的大小，即桶的数量
    size_t tableSize;

    // 哈希表中元素的数量
    size_t numElements;

    // 最大负载因子
    float maxLoadFactor = 0.75;

    // 计算键的哈希值，并将其映射到桶的索引
    size_t hash(const Key& key) const { return hashFunction(key) % tableSize; }

    // 当元素数量超过最大负载因子定义的容量时，增加桶的数量并重新分配所有键
    void rehash(size_t newSize) {
        // 创建新的桶数组
        vector<Bucket> newBuckets(newSize);

        // 遍历旧桶
        for (Bucket& bucket : buckets) {
            // 遍历桶中的每一个键
            for (HashNode& hashNode : bucket) {
                // 为键计算新的索引
                size_t	newIndex = hashFunction(hashNode.key) % newSize;
                // 将键添加到新的桶中
                newBuckets[newIndex].push_back(hashNode);
            }
        }

        // 使用移动语义更新桶数组
        buckets = move(newBuckets);
        tableSize = newSize;
    }

public:

    // 构造函数初始化哈希表
    HashTable(size_t size = 10, const Hash& hashFunc = Hash())
            : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {}

    // 插入键到哈希表中
    void insert(const Key& key, const Value& value) {
        // 检查是否需要重哈希
        if ((numElements + 1) > maxLoadFactor * tableSize) {
            if (tableSize == 0) tableSize = 1;
            rehash(tableSize * 2);
        }
        // 计算键的索引
        size_t index = hash(key);

        // 获取对应的桶
        list<HashNode>& bucket = buckets[index];

        // 如果键不在桶中，则需添加到桶中
        if (find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(HashNode(key, value));
            numElements++;
        }
    }

    void insertKey(const Key& key) {insert(key, Value{}); }

    // 从哈希表中移除键
    void erase(const Key& key) {
        // 计算键的索引
        size_t index = hash(key);

        // 获取对应的桶
        auto& bucket = buckets[index];

        // 查找键
        auto it = find(bucket.begin(), bucket.end(), key);

        // 如果找到键
        if (it != bucket.end()) {
            // 从桶中移除键
            bucket.erase(it);
            // 减少元素数量
            numElements--;
        }
    }

    // 查找键是否存在于哈希表中，找到则返回指针，找不到返回nullptr
    Value* find(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        auto ans = find(bucket.begin(), bucket.end(), key);
        if (ans != bucket.end()) {
            return &ans->value;
        }
        return nullptr;
    }


    // 获取哈希表中元素的数量
    size_t size() const { return numElements; }

    // 打印哈希表中的所有元素
    void print() const {
        for (size_t i = 0; i < buckets.size(); i++) {
            for (const HashNode& element : buckets[i]) {
                element.print();
            }
        }
        cout << endl;
    }

    // 清空哈希表
    void clear() {
        this->buckets.clear();
        this->numElements = 0;
        this->tableSize = 0;
    }
};