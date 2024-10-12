#ifndef LESSON13_H
#define LESSON13_H
#include <iostream>
#include <memory>
#include <string>

class Lesson13
{
    void task1();
    void task2();
    void task3();
public:
    Lesson13();
};
//task1
class Toy {
public:
    Toy(const std::string& name) : name_(name) {}
    std::string getNmae() { return name_; }

private:
    std::string name_;
};

class Dog {
public:
    std::shared_ptr<Toy> toy;

    void getToy(const std::string& toyName) {
        if (toy && toy->getNmae() == toyName) {
            std::cout << "I already have this toy." << std::endl;
        } else if (std::shared_ptr<Toy>(toyName) != nullptr) {
            std::cout << "Another dog is playing with this toy." << std::endl;
        } else {
            toy = std::make_shared<Toy>(toyName);
            std::cout << "Toy " << toyName << " picked up." << std::endl;
        }
    }

    void dropToy() {
        if (toy) {
            std::cout << "Toy " << toy->getNmae() << " was dropped." << std::endl;
            toy.reset();
        } else {
            std::cout << "Nothing to drop." << std::endl;
        }
    }
};
//task2
class shared_ptr_toy {
public:
    shared_ptr_toy() : ptr_(nullptr) {}
    explicit shared_ptr_toy(const std::shared_ptr<Toy>& ptr) : ptr_(ptr) {}

    shared_ptr_toy(const shared_ptr_toy& other) : ptr_(other.ptr_) {
        if (ptr_) {
            ptr_.use_count()++;
        }
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this != &other) {
            if (ptr_) {
                ptr_.use_count()--;
            }
            ptr_ = other.ptr_;
            if (ptr_) {
                ptr_.use_count()++;
            }
        }
        return *this;
    }

    ~shared_ptr_toy() {
        if (ptr_) {
            ptr_.use_count()--;
            if (ptr_.use_count() == 0) {
                ptr_.reset();
            }
        }
    }

    std::shared_ptr<Toy> ptr_;
};

shared_ptr_toy make_shared_toy(const std::string& name) {
    return shared_ptr_toy(std::make_shared<Toy>(name));
}

shared_ptr_toy make_shared_toy(const shared_ptr_toy& other) {
    return shared_ptr_toy(other.ptr_);
}
#endif // LESSON13_H
