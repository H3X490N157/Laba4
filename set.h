#include "tree.h"

template <typename T>
class RB_Tree_Set : public RB_Tree<T> {
public:

    bool Contains(T item);

    void Append(const T& item) override;

    void Union(RB_Tree_Set<T>& otherSet);

    void operator+=(RB_Tree_Set<T>& otherSet);

    RB_Tree_Set<T> Intersection(RB_Tree_Set<T>& otherSet);

    RB_Tree_Set<T> Difference(RB_Tree_Set<T>& otherSet);
};

template <typename T>
bool RB_Tree_Set<T>::Contains(T item) {
    Node<T>* current = this->root;

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
void RB_Tree_Set<T>::Append(const T& item) {
    Node<T>* current = this->root;
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

    RB_Tree<T>::Append(item);
}

template <typename T>
void RB_Tree_Set<T>::Union(RB_Tree_Set<T>& otherSet) {
    int x = otherSet.GetLength();
    for (int i = 0; i < x; ++i) {
        const T& item = otherSet[i];
        this->Append(item);  
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
        const T& item = this->Get(i);
        if (otherSet.Contains(item)) {
            result.Append(item);
        }
    }

    return result;
}

template <typename T>
RB_Tree_Set<T> RB_Tree_Set<T>::Difference(RB_Tree_Set<T>& otherSet) {
    RB_Tree_Set<T> result;
    int x = this->GetLength();
    for (int i = 0; i < x; ++i) {
        const T& item = this->Get(i);
        if (!otherSet.Contains(item)) {
            result.Append(item);
        }
    }

    return result;
}
