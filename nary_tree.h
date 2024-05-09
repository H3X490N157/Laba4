#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

template<typename T>
class NaryTree {
public:
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

    void insertHelper(Node* node, const T& val) {
        if (node == nullptr) {
            return;
        }

        if (val < node->data) {
            node->children.insert(node->children.begin(), new Node(val));
            return;
        }

        auto it = std::upper_bound(node->children.begin(), node->children.end(), val,
            [](const T& a, const Node* b) { return a < b->data; });

        node->children.insert(it, new Node(val));
    }

    void removeNode(Node* parent, Node* target) {
        if (parent == nullptr) {
            return;
        }

        auto it = std::find(parent->children.begin(), parent->children.end(), target);
        if (it != parent->children.end()) {
            deleteSubtree(*it);
            parent->children.erase(it);
            return;
        }

        for (Node* child : parent->children) {
            removeNode(child, target);
        }
    }

    NaryTree() : root(nullptr) {}

    ~NaryTree() {
        deleteSubtree(root);
    }

    void insert(const T& val) {
        if (root == nullptr) {
            root = new Node(val);
        } 
        else {
            insertHelper(root, val);
        }
    }

    bool contains(const T& val) {
        return findNode(root, val) != nullptr;
    }

    void remove(const T& val) {
        if (root == nullptr) {
            return;
        }

        removeNode(root, findNode(root, val));
    }

    std::vector<T> getSortedElements() {
        std::vector<T> elements;
        getSortedElementsHelper(root, elements);
        std::sort(elements.begin(), elements.end()); // Тупая сортировка элементов
        return elements;
    }

private:
    void getSortedElementsHelper(Node* node, std::vector<T>& elements) {
        if (node == nullptr) {
            return;
        }

        for (Node* child : node->children) {
            getSortedElementsHelper(child, elements);
        }

        elements.push_back(node->data);
    }
};