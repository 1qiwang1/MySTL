#pragma once
#include <iostream>



template <typename T>
class List {
public:
    template <typename L>
    friend ostream& operator<<(ostream& os, const List<L>& pt);

private:
    // 定义节点结构
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr):
                data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head; // 头节点指针
    Node* tail; // 尾节点指针
    size_t size;// 链表中节点的数量s

public:
    // 构造函数
    List();

    // 析构函数
    ~List();

    // 在链表末尾添加元素
    void push_back(const T& value);

    // 在链表开头添加元素
    void push_front(const T& value);

    // 获取链表中节点的数量
    size_t getSize() const;

    // 访问链表中的元素
    T& operator[](size_t index);

    // const版本的访问链表中的元素
    const T& operator[](size_t index) const;

    // 删除链表末尾的元素
    void pop_back();

    // 删除链表开头的元素
    void pop_front();

    // 获取指定值的节点
    Node* getNode(const T& value) {
        Node* node = head;
        while (node != nullptr && node->data != value) {
            node = node->next;
        }

        if (node == nullptr) {
            return nullptr;
        }
        else {
            return node;
        }
    }

    // 删除指定值的节点
    void remove(const T& value);

    // 清空链表
    void clear();
    bool empty();

    // 使用迭代器遍历链表的开始位置
    Node* begin() {
        return	tail;
    }

    // 使用迭代器遍历链表的结束位置
    Node* end() {
        return nullptr;
    }

    // 使用迭代器遍历链表的开始位置（const版本）
    const Node* begin() const {
        return	head;
    }

    // 使用迭代器遍历链表的结束位置（const版本）
    const Node* end() const {
        return nullptr;
    }

    // 打印链表中的元素
    void printElements() const;
};


template <typename T> // 构造函数
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template <typename T> // 析构函数
List<T>::~List() {
    clear();
}

template <typename T> // 在链表末尾添加元素
void List<T>::push_back(const T& value) {
    // 创建新的节点
    Node* newNode = new Node(value, nullptr, tail);

    if (tail) {
        tail->next = newNode;
    }
    else {
        head = newNode;
    }

    tail = newNode;
    size++;
}

template <typename T> // 在链表开头添加元素
void List<T>::push_front(const T& value) {
    // 创建新的节点
    Node* newNode = new Node(value, head, nullptr);

    if (head) {
        head->prev = newNode;
    }
    else {
        tail = newNode;
    }

    head = newNode;
    size++;
}

template <typename T> // 获取链表中节点的数量
size_t List<T>::getSize() const {
    return size;
}

template <typename T> // 访问链表中的元素
T& List<T>:: operator[](size_t index) {
    Node* cur = head;
    for (size_t i = 0; i < index; i++) {
        if (!cur) {
            throw out_of_range("Index out of range");
        }
        cur = cur->next;
    }
    return cur->data;
}

template <typename T> // const版本的访问链表中的元素
const T& List<T>::operator[](size_t index) const {
    Node* cur = head;
    for (size_t i = 0; i < index; i++) {
        if (!cur) {
            throw out_of_range("Index out of range");
        }
        cur = cur->next;
    }
    return cur->data;
}

template <typename T> // 删除链表末尾的元素
void List<T>::pop_back() {
    if (size > 0) {
        Node* newTail = tail->prev;
        delete tail;
        tail = newTail;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        size--;
    }
}

template <typename T> // 删除链表开头的元素
void List<T>::pop_front() {
    if (size > 0) {
        Node* newHead = head->next;
        delete head;
        head = newHead;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        size--;
    }
}



template <typename T> // 删除指定值的节点
void List<T>::remove(const T& value) {
    Node* node = head;
    while (node != nullptr && node->data != value) {
        node = node->next;
    }
    // 没有找到
    if (node == nullptr) {
        return;
    }

    // 找到了 区分情况

    // 既是头结点也是尾节点
    if (node == head && node == tail) {
        head = nullptr;
        tail = nullptr;
    }
        // 既不是头结点也不是尾节点
    else if (node != head && node != tail) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
        // 是头结点但不是尾节点
    else if (node == head && node != tail) {
        head = node->next;
        head->prev = nullptr;
    }
        // 是尾节点但不是头结点
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    size--;
    delete node;
    node = nullptr;
}

template <typename T>
bool List<T>::empty() {
    return size == 0;
}


template <typename T> // 清空链表
void List<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    size = 0;
}

template <typename T> // 打印链表中的元素
void List<T>::printElements() const {
    Node* node = head;
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

template <typename T> // 重载 << 运算符
ostream& operator<<(ostream& os, const List<T>& pt)
{
    for (typename List<T>::Node* current = pt.head; current;
         current = current->next)
    {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}