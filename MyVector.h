#pragma once
#include <iostream>



using namespace std;

template <typename T>
class Vector {
private:
    T* elements;      // 指向动态数组的指针
    size_t capacity;  // 数组的容量
    size_t size;      // 数组中元素的个数



public:
    // 构造函数
    Vector();

    // 析构函数
    ~Vector();

    // 拷贝构造函数
    Vector(const Vector& other);

    // 拷贝赋值操作符
    Vector& operator=(const Vector& other);

    // 添加元素到数组末尾
    void push_back(const T& value);

    // 获取数组中元素的个数
    size_t getSize() const;

    // 获取数组的容量
    size_t getCapacity() const;

    // 访问数组中的元素
    T& operator[](size_t index);

    // 访问数组中的元素(const版本)
    const T& operator[](size_t index) const;

    // 在指定位置插入元素
    void insert(size_t index, const T& value);

    // 删除数组末尾的元素
    void pop_back();

    // 清空数组
    void clear();

    // 使用迭代器遍历数组的开始位置
    T* begin();

    // 使用迭代器遍历数组的结束位置
    T* end();

    // 使用迭代器遍历数组的开始位置（const版本）
    const T* begin() const;

    // 使用迭代器遍历数组的结束位置（const版本）
    const T* end() const;

    // 打印数组中的元素
    void printElements() const;

private:
    // 扩容数组容量
    void reserve(size_t newCapacity);
};



template <typename T> // 构造函数
Vector<T>::Vector() : elements(nullptr), capacity(0), size(0) {}

template <typename T> // 析构函数
Vector<T>::~Vector() {
    delete[] elements;
}

template <typename T> // 拷贝构造函数
Vector<T>::Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
    elements = new T[capacity];
    copy(other.elements, other.elements + size, elements);
}





template <typename T> // 拷贝赋值操作符
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != other) {
        delete[] elements;
        capacity = other.capacity;
        size = other.size;
        elements = new T[capacity];
        copy(other.elements, other.elements + size, elements);
    }
    return *this;
}





template <typename T> // 添加元素到数组末尾
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        reserve(capacity == 0 ? 1 : 2 * capacity);
    }
    elements[size++] = value;
}


template <typename T> // 获取数组中元素的个数
size_t Vector<T>::getSize() const {
    return size;
}

template <typename T> // 获取数组的容量
size_t Vector<T>::getCapacity() const {
    return capacity;
}

template <typename T> // 访问数组中的元素
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return elements[index];
}

template <typename T> // const版本的访问数组中的元素
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return elements[index];
}
/*第一个const表示该函数是一个const成员函数，即在函数体内不能修改对象的成员变量。
第二个const表示返回值是一个常量引用，即返回的值不能被修改。*/

template <typename T> // 在指定位置插入元素
void Vector<T>::insert(size_t index, const T& value) {
    if (index > size) {
        throw out_of_range("Index out of range");
    }
    if (size == capacity) {
        reserve(capacity == 0 ? 1 : 2 * capacity);
    }
    for (size_t i = size - 1; i >= index; i--) {
        elements[i + 1] = elements[i];
    }
    elements[index] = value;
    size++;
}

template <typename T> // 删除数组末尾的元素
void Vector<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template <typename T> // 清空数组
void Vector<T>::clear() {
    size = 0;
}

template <typename T> // 使用迭代器遍历数组的开始位置
T* Vector<T>::begin() {
    return elements;
}

template <typename T> // 使用迭代器遍历数组的结束位置
T* Vector<T>::end() {
    return elements + size;
}

template <typename T> // 使用迭代器遍历数组的开始位置（const版本）
const T* Vector<T>::begin() const {
    return elements;
}

template <typename T> // 使用迭代器遍历数组的结束位置（const版本）
const T* Vector<T>::end() const {
    return elements + size;
}

template <typename T> // 打印数组中的元素
void Vector<T>::printElements() const {
    for (size_t i = 0; i < size; i++) {
        cout << elements[i] << "";
    }
    cout << endl;
}

template <typename T> // 扩容数组容量
void Vector<T>::reserve(size_t newCapacity) {
    if (newCapacity > capacity) {
        T* newElements = new T[newCapacity];
        copy(elements, elements + size, newElements);
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }
}