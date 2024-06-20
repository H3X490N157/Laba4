#include "tree.h"

template <typename T>
class RB_Tree_Set {
private:
    RB_Tree<T> tree;

public:
    bool Contains(T item);

    void Add(const T& item);

    void Union(RB_Tree_Set<T>& otherSet);

    void operator+=(RB_Tree_Set<T>& otherSet);

    void operator-=(RB_Tree_Set<T>& otherSet);

    RB_Tree_Set<T> Intersection(RB_Tree_Set<T>& otherSet);

    RB_Tree_Set<T> Difference(RB_Tree_Set<T>& otherSet);

    int GetLength();

    T& Get(int index);

    T& operator[](int index);
};

template <typename T>
bool RB_Tree_Set<T>::Contains(T item) {
    Node<T>* current = tree.root;

    while (current != nullptr) {
        if (item == current->data) {
            return true;
        } else if (item < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

template <typename T>
void RB_Tree_Set<T>::Add(const T& item) {
    Node<T>* current = tree.root;
    while (current != nullptr) {
        if (item == current->data) {
            return;
        } else if (item < current->data) {
            if (current->left == nullptr) {
                break;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                break;
            } else {
                current = current->right;
            }
        }
    }

    tree.Add(item);
}

template <typename T>
void RB_Tree_Set<T>::Union(RB_Tree_Set<T>& otherSet) {
    int x = otherSet.GetLength();
    for (int i = 0; i < x; ++i) {
        const T& item = otherSet[i];
        this->Add(item);  
    }
}

template <typename T>
void RB_Tree_Set<T>::operator+=(RB_Tree_Set<T>& otherSet) {
    this->Union(otherSet);
}

template <typename T>
RB_Tree_Set<T> RB_Tree_Set<T>::Intersection(RB_Tree_Set<T>& otherSet) {
    RB_Tree_Set<T> result;
    int x = this->GetLength();
    for (int i = 0; i < x; ++i) {
        const T& item = this->operator[](i);
        if (otherSet.Contains(item)) {
            result.Add(item);
        }
    }

    return result;
}

template <typename T>
RB_Tree_Set<T> RB_Tree_Set<T>::Difference(RB_Tree_Set<T>& otherSet) {
    RB_Tree_Set<T> result;
    int x = this->GetLength();
    for (int i = 0; i < x; ++i) {
        const T& item = this->operator[](i);
        if (!otherSet.Contains(item)) {
            result.Add(item);
        }
    }

    return result;
}

template <typename T>
void RB_Tree_Set<T>::operator-=(RB_Tree_Set<T>& otherSet) {
    *this = this->Difference(otherSet);
}

template <typename T>
int RB_Tree_Set<T>::GetLength() {
    return tree.GetLength();
}

template <typename T>
T& RB_Tree_Set<T>::operator[](int index) {
    return tree.Get(index);
}

template <typename T>
T& RB_Tree_Set<T>::Get(int index) {
    return tree.Get(index);
}