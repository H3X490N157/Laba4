#include "sequence.h"
#include <iostream>
#include <stack>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(T data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RB_Tree : public Sequence<T> {
private:
    Node<T>* root;
    int length;

    void RotateLeft(Node<T>*&);
    void RotateRight(Node<T>*&);
    void FixInsert(Node<T>*&);
    void Transplant(Node<T>*, Node<T>*);
    void DeleteFix(Node<T>*);
    Node<T>* Minimum(Node<T>* node);
    Node<T>* Maximum(Node<T>* node);
    Node<T>* GetNode(int index);
    void DeleteNode(Node<T>* node);
    void InOrderPrint(Node<T>* node);

public:
    RB_Tree();
    ~RB_Tree();
    
    T& GetFirst() override;
    T& GetLast() override;
    T& Get(int index) override;
    T& operator[](int index) override;
    int GetLength() override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    void PrintTree();
};

template <typename T>
RB_Tree<T>::RB_Tree() : root(nullptr), length(0) {}

template <typename T>
RB_Tree<T>::~RB_Tree() {
    DeleteNode(root);
}

template <typename T>
void RB_Tree<T>::DeleteNode(Node<T>* node) {
    if (node == nullptr) return;
    DeleteNode(node->left);
    DeleteNode(node->right);
    delete node;
}

template <typename T>
T& RB_Tree<T>::GetFirst() {
    Node<T>* minNode = Minimum(root);
    return minNode->data;
}

template <typename T>
T& RB_Tree<T>::GetLast() {
    Node<T>* maxNode = Maximum(root);
    return maxNode->data;
}

template <typename T>
T& RB_Tree<T>::Get(int index) {
    Node<T>* node = GetNode(index);
    return node->data;
}

template <typename T>
T& RB_Tree<T>::operator[](int index) {
    return Get(index);
}

template <typename T>
int RB_Tree<T>::GetLength() {
    return length;
}

template <typename T>
void RB_Tree<T>::Append(const T& item) {
    Node<T>* newNode = new Node<T>(item);
    if (root == nullptr) {
        newNode->color = BLACK;
        root = newNode;
    } else {
        Node<T>* parent = nullptr;
        Node<T>* current = root;
        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        newNode->parent = parent;
        if (newNode->data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        FixInsert(newNode);
    }
    length++;
}

template <typename T>
void RB_Tree<T>::Prepend(const T& item) {
    Append(item);  // Для красно-чёрного дерева Append и Prepend могут быть идентичны
}

template <typename T>
void RB_Tree<T>::RotateLeft(Node<T>*& node) {
    Node<T>* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

template <typename T>
void RB_Tree<T>::RotateRight(Node<T>*& node) {
    Node<T>* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

template <typename T>
void RB_Tree<T>::FixInsert(Node<T>*& node) {
    Node<T>* parent = nullptr;
    Node<T>* grandparent = nullptr;
    while (node != root && node->color != BLACK && node->parent->color == RED) {
        parent = node->parent;
        grandparent = node->parent->parent;
        if (parent == grandparent->left) {
            Node<T>* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    RotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                RotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node<T>* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    RotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                RotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

template <typename T>
Node<T>* RB_Tree<T>::Minimum(Node<T>* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
Node<T>* RB_Tree<T>::Maximum(Node<T>* node) {
    while (node->right != nullptr)
        node = node->right;
    return node;
}

template <typename T>
Node<T>* RB_Tree<T>::GetNode(int index) {
    Node<T>* current = root;
    int count = 0;
    std::stack<Node<T>*> stack;
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        if (count == index)
            return current;
        count++;
        current = current->right;
    }
    return nullptr;
}

template <typename T>
void RB_Tree<T>::InOrderPrint(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    InOrderPrint(node->left);
    std::cout << node->data << " ";
    InOrderPrint(node->right);
}

template <typename T>
void RB_Tree<T>::PrintTree() {
    InOrderPrint(root);
    std::cout << std::endl;
}
