#ifndef LESSON15_H
#define LESSON15_H
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <string>
#include <random>
#include <array>

class Lesson15
{
    void task1();
    void task2();
    void task3();
    void task4();
public:
    Lesson15();
};
//task1
class Store {
public:
    std::map<std::string, int> products;

    void addProduct(const std::string& productID, int quantity) {
        products[productID] += quantity;
    }

    void removeProduct(const std::string& productID, int quantity) {
        if (products.find(productID) != products.end()) {
            if (quantity > products[productID]) {
                throw std::runtime_error("Количество превышает остаток товара.");
            }
            products[productID] -= quantity;
        } else {
            throw std::invalid_argument("Артикул не найден в магазине.");
        }
    }
};

class Cart {
public:
    std::map<std::string, int> items;

    void addItem(const std::string& productID, int quantity) {
        if (items.find(productID) != items.end()) {
            items[productID] += quantity;
        } else {
            items[productID] = quantity;
        }
    }

    void removeItem(const std::string& productID, int quantity) {
        if (items.find(productID) != items.end()) {
            if (quantity > items[productID]) {
                throw std::runtime_error("Количество превышает остаток товара в корзине.");
            }
            items[productID] -= quantity;
        } else {
            throw std::invalid_argument("Артикул не найден в корзине.");
        }
    }
};

//task2
class GameOverException : public std::exception {};

class Field {
public:
    enum class ObjectType { FISH, BOOT };

    std::array<ObjectType, 9> objects;

    void placeFish() {
        objects[std::rand() % 9] = ObjectType::FISH;
    }

    void placeBoot() {
        int position = std::rand() % 9;
        while (objects[position] != ObjectType::EMPTY) {
            position = std::rand() % 9;
        }
        objects[position] = ObjectType::BOOT;
    }

    ObjectType getObject(int position) {
        return objects[position];
    }
};

class Fish {
public:
    Fish() {
        throw GameOverException();
    }
};

class Boot {
public:
    Boot() {
        throw GameOverException();
    }
};
//task3
template <typename Key, typename Value>
struct Entry {
    Key key;
    Value value;
};

template <typename Key, typename Value>
class Registry {
public:
    std::vector<Entry<Key, Value>> entries;

    void add(const Key& key, const Value& value) {
        entries.push_back({key, value});
    }

    void remove(const Key& key) {
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->key == key) {
                entries.erase(it);
                return;
            }
        }
    }

    void print() {
        for (const auto& entry : entries) {
            std::cout << entry.key << " -> " << entry.value << std::endl;
        }
    }

    template <typename Predicate>
    void find(Predicate predicate) {
        for (const auto& entry : entries) {
            if (predicate(entry.key)) {
                std::cout << entry.key << " -> " << entry.value << std::endl;
            }
        }
    }
};

//task4
template <typename T>
void input(T array[]) {
    std::cout << "Введите " << n << " элементов: ";
    for (int i = 0; i < 8; ++i) {
        std::cin >> array[i];
    }
}

template <typename T>
T calculateMean(const T array[]) {
    T sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum +=array[i];
    }
    return sum / n;
}
#endif // LESSON15_H
