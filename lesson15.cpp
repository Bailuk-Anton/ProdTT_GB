#include "lesson15.h"

void Lesson15::task1()
{
    Store store;
    Cart cart;

    // Добавление продуктов в магазин
    store.addProduct("apple", 10);
    store.addProduct("banana", 20);
    store.addProduct("pear", 30);

    try {
        // Добавление товаров в корзину
        cart.addItem("apple", 5);
        cart.addItem("banana", 10);
        cart.addItem("pear", 20);

        // Удаление товаров из корзины
        cart.removeItem("apple", 2);
        cart.removeItem("banana", 5);
        cart.removeItem("pear", 10);

        // Проверка содержимого корзины
        for (const auto& item : cart.items) {
            std::cout << "Артикул: " << item.first << ", Количество: " << item.second << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Lesson15::task2()
{
    std::srand(std::time(nullptr));

    Field gameField;
    gameField.placeFish();
    gameField.placeBoot();
    gameField.placeBoot();

    try {
        while (true) {
            int sector = std::rand() % 9;
            if (gameField.getObject(sector) == Field::ObjectType::FISH) {
                throw Fish();
            } else if (gameField.getObject(sector) == Field::ObjectType::BOOT) {
                throw Boot();
            }
        }
    } catch (const Fish&) {
        std::cout << "Выловили рыбу!" << std::endl;
        break;
    } catch (const Boot&) {
        std::cout << "Выловили сапог!" << std::endl;
        throw GameOverException();
    }
}

void Lesson15::task3()
{
    Registry<int, std::string> registry;

    std::string command;
    while (true) {
        std::cout << "Введите команду (add, remove, print, find, quit): ";
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        } else if (command == "add") {
            int key;
            std::string value;
            std::cout << "Введите ключ: ";
            std::cin >> key;
            std::cout << "Введите значение: ";
            std::getline(std::cin, value);
            registry.add(key, value);
        } else if (command == "remove") {
            int key;
            std::cout << "Введите ключ: ";
            std::cin >> key;
            registry.remove(key);
        } else if (command == "print") {
            registry.print();
        } else if (command == "find") {
            int key;
            std::cout << "Введите ключ: ";
            std::cin >> key;
            registry.find([key](const int& k) { return k == key; });
        } else {
            std::cout << "Неизвестная команда." << std::endl;
        }
    }
}

void Lesson15::task4()
{
    constexpr size_t ARRAY_SIZE = 8;
    double array[ARRAY_SIZE];

    input(array, ARRAY_SIZE);
    double mean = calculateMean(array, ARRAY_SIZE);

    std::cout << "Среднее арифметическое: " << mean << std::endl;
}

Lesson15::Lesson15()
{

}
