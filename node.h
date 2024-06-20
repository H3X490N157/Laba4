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