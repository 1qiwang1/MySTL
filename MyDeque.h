#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Deque {
private:
    T* elements;
    size_t capacity;
    size_t frontIndex;
    size_t backIndex;
    size_t size;

public:
    // 构造函数
    Deque();

    // 析构函数
    ~Deque();

    // 在deque的前端插入元素
    void push_front(const T& value);

    // 在deque的后端插入元素
    void push_back(const T& value);

    // 从deque的前端移除元素
    void pop_front();

    // 从deque的后端移除元素
    void pop_back();

    // 随机访问元素
    T& operator[](int index);

    // 获取deque中的元素数量
    size_t getSize() const;

    // 清空deque
    void clear();

    // 打印deque中的元素
    void printElements() const;

private:
    // 扩展数组容量
    void resize();

};

template<typename T> // 构造函数
Deque<T>::Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}

template<typename T> // 析构函数
Deque<T>::~Deque() {
    clear();
    delete[] elements;
}

template<typename T> // 在deque的前端插入元素
void Deque<T>::push_front(const T& value) {
    // 检查是否需要扩展数组容量
    if (size == capacity) {
        resize();
    }

    frontIndex = (frontIndex - 1 + capacity) % capacity;
    elements[frontIndex] = value;
    size++;
}

template<typename T> // 在deque的后端插入元素
void Deque<T>::push_back(const T& value) {
    // 检查是否需要扩展数组容量
    if (size == capacity) {
        resize();
    }

    elements[backIndex] = value;
    backIndex = (backIndex + 1) % capacity;
    size++;
}

template<typename T> // 从deque的前端移除元素
void Deque<T>::pop_front() {
    if (size == 0) {
        throw out_of_range("Deque is empty");
    }

    // 删除元素不需要显式地删除, 以后新追加元素会自动覆盖
    // 计算新的前端索引
    frontIndex = (frontIndex + 1) % capacity;
    size--;
}


template<typename T> // 从deque的后端移除元素
void Deque<T>::pop_back() {
    if (size == 0) {
        throw out_of_range("Deque is empty");
    }

    // 删除元素不需要显式地删除, 以后新追加元素会自动覆盖
    // 计算新的后端索引
    backIndex = (backIndex - 1 + capacity) % capacity;
    size--;
}


template<typename T> // 随机访问元素
T& Deque<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return elements[(frontIndex + index) % capacity];
}

template<typename T> // 获取deque中的元素数量
size_t Deque<T>::getSize() const {
    return size;
}


template<typename T> // 清空deque
void Deque<T>::clear() {
    while (size > 0) {
        pop_front();
    }
}

template<typename T> // 打印deque中的元素
void Deque<T>::printElements() const {
    size_t index = frontIndex;
    for (size_t i = index; i < size; i++) {
        cout << elements[index] << " ";
        index = (index + 1) % capacity;
    }
    cout << endl;
}


template<typename T> // 扩展数组容量
void Deque<T>::resize() {
    // 计算新的容量
    size_t newCapacity = (capacity == 0) ? 1 : 2 * capacity;

    // 创建新的数组
    T* newElements = new T[newCapacity];

    // 复制元素到新的数组
    size_t index = frontIndex;
    for (size_t i = 0; i < size; i++) {
        newElements[i] = elements[index];
        index = (index + 1) % capacity;
    }

    delete[] elements;

    elements = newElements;
    capacity = newCapacity;
    frontIndex = 0;
    backIndex = size;
}