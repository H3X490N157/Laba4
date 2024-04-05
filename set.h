#pragma once 
#include "nary_tree.h"


template<typename T>
class Set : public NaryTree<T> {
public:
    Set() : NaryTree<T>() {}

    void insert(const T& val) {
        if (this->find(val) == nullptr) {
            if (this->root == nullptr) {
                this->root = new typename NaryTree<T>::Node(val);
            } 
            else {
                this->root->children.push_back(new typename NaryTree<T>::Node(val));
            }
        }
    }

    void remove(const T& val) {
        typename NaryTree<T>::Node* target = this->find(val);
        if (target != nullptr) {
            if (this->root == target) {
                delete target;
                this->root = nullptr;
            } 
            else {
                typename NaryTree<T>::Node* parent = this->findParent(this->root, val);
                if (parent != nullptr) {
                    auto it = parent->children.begin();
                    while (it != parent->children.end()) {
                        if (*it == target) {
                            this->deleteSubtree(*it);
                            it = parent->children.erase(it);
                            break;
                        }
                        ++it;
                    }
                }
            }
        }
    }

    bool contains(const T& val) {
        return this->find(val) != nullptr;
    }

private:
    typename NaryTree<T>::Node* findParent(typename NaryTree<T>::Node* node, const T& val) {
        if (node == nullptr) {
            return nullptr;
        }
        for (typename NaryTree<T>::Node* child : node->children) {
            if (child->data == val) {
                return node;
            }
            typename NaryTree<T>::Node* found = findParent(child, val);
            if (found != nullptr){
                return found;
            }
        }
        return nullptr;
    }
};