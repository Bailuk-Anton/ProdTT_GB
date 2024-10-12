#ifndef LESSON11_H
#define LESSON11_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <map>
#include <math.h>
#include <algorithm>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <queue>

class Lesson11
{
    void task1();
    void task2();
public:
    Lesson11();
};
//task1
class Talent {
public:
    virtual void perform() = 0;
};

class Swimming : public Talent {
public:
    void perform() override {
        std::cout << "I'm swimming like a fish!" << std::endl;
    }
};

class Dancing : public Talent {
public:
    void perform() override {
        std::cout << "Shake my tail, I'm dancing!" << std::endl;
    }
};

class Counting : public Talent {
public:
    void perform() override {
        std::cout << "One, two, three... I'm counting!" << std::endl;
    }
};

class Dog {
public:
    std::string name;
    std::vector<Talent*> talents;

    explicit Dog(const std::string& name) : name(name) {}

    void addTalent(Talent* talent) {
        talents.push_back(talent);
    }

    void removeTalent(Talent* talent) {
        for (auto it = talents.begin(); it != talents.end(); ++it) {
            if (*it == talent) {
                talents.erase(it);
                break;
            }
        }
    }

    void show_talents() {
        std::cout << "This is " << name << " and it has some talents:" << std::endl;
        for (const auto& talent : talents) {
            talent->perform();
        }
    }
};
//task2
// Интерфейс Shape
class Shape {
public:
    virtual double square() = 0;
    virtual BoundingBoxDimensions dimensions() = 0;
    virtual std::string type() = 0;
};

// Структура для хранения размеров прямоугольника
struct BoundingBoxDimensions {
    double width;
    double height;
};

// Класс Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) : radius(radius) {}

    double square() override {
        return M_PI * pow(radius, 2);
    }

    BoundingBoxDimensions dimensions() override {
        return {2 * radius, 2 * radius};
    }

    std::string type() override {
        return "Circle";
    }
};

// Класс Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double square() override {
        return width * height;
    }

    BoundingBoxDimensions dimensions() override {
        return {width, height};
    }

    std::string type() override {
        return "Rectangle";
    }
};

// Класс Triangle
class Triangle : public Shape {
private:
    double a;
    double b;
    double c;

public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double square() override {
        double semiperimeter = (a + b + c) / 2.0;
        return sqrt(semiperimeter * (semiperimeter - a) * (semiperimeter - b) * (semiperimeter - c));
    }

    BoundingBoxDimensions dimensions() override {
        double semiperimeter = (a + b + c) / 2.0;
        double r = a * b * c / (4 * sqrt(semiperimeter * (semiperimeter - a) * (semiperimeter - b) * (semiperimeter - c)));
        return {2 * r, 2 * r};
    }

    std::string type() override {
        return "Triangle";
    }
};

// Функция для вывода параметров фигуры
void printParams(Shape* shape) {
    std::cout << "Type: " << shape->type() << std::endl;
    std::cout << "Square: " << shape->square() << std::endl;
    BoundingBoxDimensions dims = shape->dimensions();
    std::cout << "Width: " << dims.width << std::endl;
    std::cout << "Height: " << dims.height << std::endl;
}
#endif // LESSON11_H
