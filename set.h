#pragma once
#include "nary_tree.h"

template<typename T>
class Set {
private:
    NaryTree<T> tree;

public:
    bool contains(const T& val) {
        return tree.contains(val);
    }

    void insert(const T& val) {
        if (!tree.contains(val)){
            tree.insert(val);
        }
    }

    void remove(const T& val) {
        tree.remove(val);
    }

    T find(size_t index) {
        std::vector<T> sortedElements = tree.getSortedElements();
        if (index >= sortedElements.size()) {
            throw std::out_of_range("Некорректный индекс");
        }
        return sortedElements[index];
    }

    T operator[](size_t index) {
        return find(index);
    }
};