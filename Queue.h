#pragma once
#include <deque>
#include <iostream>

template<typename T, typename Containor = std::deque<T>>
class Queue {
public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!empty()) {
            data.pop_front();
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }

    T& front() {
        if (!empty()) {
            return data.front();
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }

    T& back() {
        if (!empty()) {
            return data.back();
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }

    bool empty() {
        return data.size() == 0;
    }

    size_t size() const {
        return data.size();
    }

private:
    Containor data;
};

