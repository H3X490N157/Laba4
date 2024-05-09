#include "set.h"

#include <cassert>
#include <string>


void testInsert() {
    Set<int> set;
    assert(set.contains(5) == false);
    set.insert(5);
    assert(set.contains(5) == true);
    set.insert(3);
    assert(set.contains(3) == true);
    set.insert(7);
    assert(set.contains(7) == true);
    set.insert(2);
    assert(set.contains(2) == true);
    set.insert(4);
    assert(set.contains(4) == true);
}

void testContains() {
    Set<int> set;
    assert(set.contains(5) == false);
    set.insert(5);
    assert(set.contains(5) == true);
    assert(set.contains(3) == false);
    set.insert(3);
    assert(set.contains(3) == true);
    assert(set.contains(7) == false);
    set.insert(7);
    assert(set.contains(7) == true);
    assert(set.contains(2) == false);
    set.insert(2);
    assert(set.contains(2) == true);
    assert(set.contains(4) == false);
    set.insert(4);
    assert(set.contains(4) == true);
}

void testRemove() {
    Set<int> set;
    set.insert(5);
    set.insert(3);
    set.insert(7);
    set.insert(2);
    set.insert(4);

    assert(set.contains(3) == true);
    set.remove(3);
    assert(set.contains(3) == false);

    assert(set.contains(5) == true);
    set.remove(5);
    assert(set.contains(2) == true);
    set.remove(2);
    assert(set.contains(2) == false);

    assert(set.contains(7) == true);
    set.remove(7);
    assert(set.contains(7) == false);

    assert(set.contains(4) == true);
    set.remove(4);
    assert(set.contains(4) == false);
}

void testFindElementByIndex() {
    Set<int> set;
    set.insert(5);
    set.insert(3);
    set.insert(7);
    set.insert(2);
    set.insert(4);

    assert(set.find(0) == 2);
    assert(set.find(1) == 3);
    assert(set.find(2) == 4);
    assert(set[3] == 5);
    assert(set[4] == 7);
}

int main() {
    Set<int> set;
    int choice = 1;
    int value;
    size_t index;
    std::string func_name;

    std::cout << "Меню:" << std::endl;
    std::cout << "1. Вставка элемента" << std::endl;
    std::cout << "2. Проверка существования элемента" << std::endl;
    std::cout << "3. Удаление элемента" << std::endl;
    std::cout << "4. Поиск элемента по индексу" << std::endl;
    std::cout << "5. Выбор авто-функции для тестирования" << std::endl;
    std::cout << "Все остальные числа. Выход" << std::endl;
    do {
        std::cout << "Введите выбранную опцию: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите значение для вставки: ";
                std::cin >> value;
                set.insert(value);
                std::cout << "Значение " << value << " вставлено." << std::endl;
                break;
            case 2:
                std::cout << "Введите значение для проверки существвования: ";
                std::cin >> value;
                if (set.contains(value)) {
                    std::cout << "Значение " << value << " есть в множестве." << std::endl;
                } else {
                    std::cout << "Значение " << value << " отсутствует в множестве." << std::endl;
                }
                break;
            case 3:
                std::cout << "Введите значение для удаления ";
                std::cin >> value;
                set.remove(value);
                std::cout << "Значение " << value << " удаление." << std::endl;
                break;
            case 4:
                std::cout << "Введите индекс для поиска по нему: ";
                std::cin >> index;
                try {
                    std::cout << "По индексу " << index << " обнаружено значение: " << set.find(index) << std::endl;
                } 
                catch (std::out_of_range& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 5:
                std::cout << "Введите название функции (указывать с кругыми скобками и без пробелов на конце)" << std::endl; //специально, чтобы текстовый квест был
                std::cin >> func_name;
                if (func_name == "testInsert()"){
                    testInsert();
                    std::cout << "testInsert() успешно выполнена" << std::endl;
                }
                else if (func_name == "testContains()"){
                    testContains();
                    std::cout << "testContains() успешно выполнена" << std::endl;
                }
                else if (func_name == "testRemove()"){
                    testRemove();
                    std::cout << "testRemove() успешно выполнена" << std::endl;
                }
                else if (func_name == "testFindElementByIndex()"){
                    testFindElementByIndex();
                    std::cout << "testFindElementByIndex() успешно выполнена" << std::endl;
                }
                else{
                    std::cout << "Некорректное название функции. Продолжайте угадывать)" << std::endl;
                }
                break;
            default:
                std::cout << "До свидания." << std::endl;
                break;
        }
    } while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5);

    return 0;
}