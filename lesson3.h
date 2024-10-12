#ifndef LESSON3_H
#define LESSON3_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <algorithm>

class Lesson3
{
    void task1();
    void task2();
    void task3();
    void task4();
public:
    Lesson3();
};

struct Payment {
    std::string name;
    std::string surname;
    std::string date;
    int amount;
};
//task1-------------------------
class PaymentBook {
public:
    PaymentBook(const std::string& filename) : filename(filename) {}

    void readPayments() {
        std::ifstream inputFile(filename);
        if (!inputFile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::vector<Payment> payments;
        std::string line;
        while (getline(inputFile, line)) {
            std::istringstream ss(line);

            Payment p;
            std::string token;
            while (getline(ss, token, ' ')) {
                if (token == "") continue;

                if (p.name.empty()) {
                    p.name = token;
                } else if (p.surname.empty()) {
                    p.surname = token;
                } else if (p.date.empty()) {
                    p.date = token;
                } else {
                    try {
                        p.amount = std::stoi(token);
                    } catch (...) {
                        std::cerr << "Invalid amount: " << token << std::endl;
                        return;
                    }
                }
            }

            if (!p.name.empty() && !p.surname.empty() && !p.date.empty() && p.amount > 0) {
                payments.push_back(p);
            }
        }

        inputFile.close();
        this->payments = payments;
    }

    void writePayments() {
        std::ofstream outputFile(filename, std::ios::app);
        if (outputFile) {
            for (const auto& p : payments) {
                outputFile << p.name << " " << p.surname << " " << p.date << " " << p.amount << '\n';
            }
            outputFile.close();
        } else {
            std::cerr << "Failed to append data to file: " << filename << std::endl;
        }
    }

    void addPayment(const Payment& p) {
        payments.push_back(p);
        writePayments();
    }

    void listPayments() {
        for (const auto& p : payments) {
            std::cout << p.name << " " << p.surname << " " << p.date << " " << p.amount << '\n';
        }
    }

private:
    std::string filename;
    std::vector<Payment> payments;
};
//task2-------------------------
// Структура для участка
struct Plot {
    int id;
    std::vector<Building> buildings;
};

// Общий базовый класс для всех зданий
struct Building {
    virtual ~Building() = default;
    int id;
    float area;
};

// Жилой дом
struct House : public Building {
    std::vector<Room> rooms;
    std::vector<Floor> floors;
};

// Структура для комнаты
struct Room {
    std::string type;
    float area;
};

// Структура для этажа
struct Floor {
    int num_rooms;
    float ceiling_height;
};

// Гараж
struct Garage : public Building {};

// Бытовка (сарай)
struct Shed : public Building {};

// Баня
struct Bathhouse : public Building {
    Pipe pipe;
};

// Структура для печной трубы
struct Pipe {
    float diameter;
    float length;
};

//task3--------------------------------

struct Vector2D {
    double x;
    double y;

    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double _x, double _y) : x(_x), y(_y) {}

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << "(" << std::setprecision(6) << v.x << ", " << v.y << ")";
    }
};

Vector2D add(const Vector2D& u, const Vector2D& v) {
    return Vector2D(u.x + v.x, u.y + v.y);
}

Vector2D subtract(const Vector2D& u, const Vector2D& v) {
    return Vector2D(u.x - v.x, u.y - v.y);
}

Vector2D scale(const Vector2D& v, double k) {
    return Vector2D(v.x * k, v.y * k);
}

double length(const Vector2D& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector2D normalize(const Vector2D& v) {
    return scale(v, 1.0 / length(v));
}

//task4-------------------------------
#endif // LESSON3_H
