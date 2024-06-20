#include "set.h"
#include <cassert>

//убрать наследование (сделано), Set композировал дерева, починить принт на поэлементное действие через енумерацию
void testRBTree() {
    RB_Tree<int> tree;

    assert(tree.GetLength() == 0);
    tree.Add(10);
    tree.Add(20);
    tree.Add(30);
    assert(tree.GetLength() == 3);

    assert(tree.GetFirst() == 10);
    assert(tree.GetLast() == 30);

    assert(tree.Get(0) == 10);
    assert(tree.Get(1) == 20);
    assert(tree.Get(2) == 30);
    assert(tree[0] == 10);
    assert(tree[1] == 20);
    assert(tree[2] == 30);

    tree.Add(5);
    assert(tree.GetLength() == 4);
    assert(tree.GetFirst() == 5);
    assert(tree.Get(0) == 5);
    assert(tree.Get(1) == 10);
    assert(tree.Get(2) == 20);
    assert(tree.Get(3) == 30);

    RB_Tree<std::string> tree_char;
    tree_char.Add("This is fine");
    (tree_char.Get(0) == "This is fine"); 

    std::cout << "Все тесты для дерева, содержащего элементы ";
    std::cout << tree.PrintTree() << std::endl;
    std::cout << "пройдены успешно!" << std::endl;


}

void testRBTreeSet() {
    RB_Tree_Set<int> set1;
    RB_Tree_Set<int> set2;

    set1.Add(10);
    set1.Add(20);
    set1.Add(30);
    assert(set1.Contains(10));
    assert(set1.Contains(20));
    assert(set1.Contains(30));
    assert(!set1.Contains(40));

    set2.Add(20);
    set2.Add(30);
    set2.Add(40);
    assert(set2.Contains(20));
    assert(set2.Contains(30));
    assert(set2.Contains(40));
    assert(!set2.Contains(10));

    set1.Union(set2);
    assert(set1.Contains(10));
    assert(set1.Contains(20));
    assert(set1.Contains(30));
    assert(set1.Contains(40));

    RB_Tree_Set<int> set3;
    set3.Add(50);
    set3.Add(60);
    RB_Tree_Set<int> resultSet = set1;
    resultSet += set3;
    assert(resultSet.Contains(10));
    assert(resultSet.Contains(20));
    assert(resultSet.Contains(30));
    assert(resultSet.Contains(40));
    assert(resultSet.Contains(50));
    assert(resultSet.Contains(60));

    RB_Tree_Set<int> set4;
    RB_Tree_Set<int> set5;

    set4.Add(30);
    set4.Add(10);
    set4.Add(20);
    set4.Add(30);

    set5.Add(20);
    set5.Add(50);
    set5.Add(40);

    RB_Tree_Set<int> intersectionSet = set1.Intersection(set2);
    RB_Tree_Set<int> differenceSet = set1.Difference(set2);
    assert(intersectionSet.Contains(20));
    assert(!intersectionSet.Contains(10));
    assert(!differenceSet.Contains(20));
    assert(differenceSet.Contains(10));

    assert(set4[0] == 10);
    assert(set4[1] == 20);
    assert(set4[2] == 30);

    assert(set5.Get(0) == 20);
    assert(set5.Get(1) == 40);
    assert(set5.Get(2) == 50);

    std::cout << "Все тесты для Set пройдены успешно" << std::endl;

}

int main() {
    char choice = '1';
    do {
        std::cout << "Выберите тест:\n";
        std::cout << "1. Тест для красно-чёрного дерева\n";
        std::cout << "2. Тест для множества\n";
        std::cout << "Любой другой символ означает выход\n";
        std::cout << "Введите: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                testRBTree();
                std::cout << "\n";
                break;
            case '2':
                testRBTreeSet();
                std::cout << "\n";
                break;
            default:
                std::cout << "До свидания\n";
        }
    } while (choice == '1' || choice == '2');
}

