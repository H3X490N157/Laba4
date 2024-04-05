#include <iostream>
#include <vector>
#include <cassert>
#pragma once 

template<typename T>
class NaryTree {
public:
///а дальше костыль с Нодой
    struct Node {
        T data;
        std::vector<Node*> children;

        explicit Node(const T& val) : data(val) {}
    };

    Node* root;

    Node* findNode(Node* node, const T& val) {
        if (node == nullptr) return nullptr;
        if (node->data == val) return node;

        for (Node* child : node->children) {
            Node* found = findNode(child, val);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

    void deleteSubtree(Node* node) {
        if (node == nullptr) return;

        for (Node* child : node->children) {
            deleteSubtree(child);
        }
        delete node;
    }

    void insertHelper(Node* node, const T& parentVal, const T& val) {
        if (node == nullptr) {
            return;
        }

        if (node->data == parentVal) {
            node->children.push_back(new Node(val));
            return;
        }

        for (Node* child : node->children) {
            insertHelper(child, parentVal, val);
        }
    }

    void removeNode(Node* parent, Node* target) {
        if (parent == nullptr) {
            return;
        }

        auto it = parent->children.begin();
        while (it != parent->children.end()) {
            if (*it == target) {
                deleteSubtree(*it);
                it = parent->children.erase(it);
                return;
            }
            ++it;
        }

        for (Node* child : parent->children) {
            removeNode(child, target);
        }
    }

    NaryTree() : root(nullptr) {}

    ~NaryTree() {
        deleteSubtree(root);
    }

    void insert(const T& parentVal, const T& val) {
        if (root == nullptr) {
            root = new Node(parentVal);
            root->children.push_back(new Node(val));
        } 
        else {
            insertHelper(root, parentVal, val);
        }
    }

    Node* find(const T& val) {
        return findNode(root, val);
    }

    void remove(const T& val) {
        if (root == nullptr) {
            return;
        }

        if (root->data == val) {
            deleteSubtree(root);
            root = nullptr;
            return;
        }

        removeNode(root, find(val));
    }

    NaryTree* extractSubtree(const T& val) {
        Node* target = find(val);
        if (target == nullptr) {
            return nullptr;
        }
        NaryTree* subtree = new NaryTree;
        subtree->root = target;
        remove(val);
        return subtree;
    }
};