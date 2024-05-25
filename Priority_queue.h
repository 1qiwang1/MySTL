#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, typename Container = std::vector<T>>
class Priority_queue {
public:
    Priority_queue() = default;

    explicit Priority_queue(const Container& c) : data(c) {
        int size = data.size();
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void push(const T& val) {
        data.push(val);
        heapifyUp();
    }

    void pop() {
        if (!empty()) {
            std::swap(data[0], data[data.size() - 1]);
            data.pop_back();
            heapifyDown();
        } else {
            throw std::runtime_error("Priority_queue is empty");
        }
    }

    T& top() {
        if (!empty()) {
            return data[0];
        } else {
            throw std::runtime_error("Priority_queue is empty");
        }
    }

    bool empty() {
        return data.size() == 0;
    }

    size_t size() {
        return data.size();
    }


private:
    Container data;

// 构建的是大顶堆
    // 辅助函数：向上调整元素以维护堆性质
    void heapifyUp() {
        int index = data.size() - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[index] > data[parentIndex]) {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // 辅助函数：向下调整元素以维护堆性质
    void heapifyDown(int index) {
        int size = data.size();
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && data[leftChild] > data[index]) {
               largest = leftChild;
            }

            if (rightChild < size && data[rightChild] > data[index]) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(data[largest], data[index]);
            } else {
                break;
            }
        }
    }

};

