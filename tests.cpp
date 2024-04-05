#include "set.h"

void tree_tests(){
    NaryTree<int> tree;

    tree.insert(1, 2);
    tree.insert(1, 3);
    tree.insert(2, 4);
    tree.insert(2, 5);
    tree.insert(3, 6);

    assert(tree.find(2) != nullptr);
    assert(tree.find(5) != nullptr);
    assert(tree.find(7) == nullptr);

    tree.remove(2);
    assert(tree.find(2) == nullptr);
    assert(tree.find(4) == nullptr);

    NaryTree<int>* subtree = tree.extractSubtree(3);
    assert(subtree != nullptr);
}

void runSetTests() {
    Set<int> set;

    set.insert(5);
    set.insert(3);
    set.insert(7);
    set.insert(3); 

    assert(set.contains(5));
    assert(set.contains(3));
    assert(set.contains(7));
    assert(!set.contains(4)); 

    set.remove(3);
    set.remove(7);

    assert(!set.contains(3));
    assert(!set.contains(7));
    assert(set.contains(5)); 
    assert(set.root->children.size() == 0);
}


int main() {
    tree_tests();
    runSetTests();
    
    std::cout << "Ещё один успех!" << std::endl;

    return 0;
}