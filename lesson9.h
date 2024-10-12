#ifndef LESSON9_H
#define LESSON9_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <map>
#include <math.h>
#include <algorithm>

class Lesson9
{
    void task1();
    void task2();
    void task3();
public:
    Lesson9();
};
//task1
class Tree {
public:
    int big_branches;
    int medium_branches;
    std::vector<Branch> branches;
    std::vector<Home> homes;

    Tree(int big_branches, int medium_branches) : big_branches(big_branches), medium_branches(medium_branches) {}

    void generate_tree() {
        std::vector<Branch> temp_branches;
        for (int i = 0; i < big_branches; ++i) {
            Branch branch(medium_branches);
            temp_branches.push_back(branch);
        }
        branches = temp_branches;
        homes = std::vector<Home>();
        for (const auto& branch : branches) {
            for (const auto& home : branch.homes) {
                homes.push_back(home);
            }
        }
    }

    void assign_elf(int home_index) {
        std::string name = get_user_input();
        if (name != "None") {
            homes[home_index].assign_elf(name);
        }
    }

    int count_neighbours(int elf_index) {
        int neighbours = 0;
        for (int i = 0; i < homes.size(); ++i) {
            if (i != elf_index && homes[i].has_elf()) {
                neighbours += 1;
            }
        }
        return neighbours;
    }
};

class Branch {
public:
    int sub_branches;
    std::vector<Home> homes;

    Branch(int sub_branches) : sub_branches(sub_branches) {}

    void generate_branch() {
        std::vector<Home> temp_homes;
        for (int i = 0; i < sub_branches; ++i) {
            Home home;
            temp_homes.push_back(home);
        }
        homes = temp_homes;
    }
};

class Home {
public:
    Branch* branch;
    Elf elf;
    std::vector<Home*> neighbours;

    Home(Branch* branch) : branch(branch) {}

    void assign_elf(const std::string& name) {
        elf.name = name;
    }

    bool has_elf() {
        return elf.name != "None";
    }
};

class Elf {
public:
    std::string name;
};

std::string get_user_input() {
    std::string name;
    std::cout << "Enter the name of the elf: ";
    std::getline(std::cin, name);
    return name;
}
//task2
enum Color { Red, Blue, Green, None };

class Shape {
protected:
    double centerX;
    double centerY;
    Color color;

public:
    Shape(double centerX, double centerY, Color color) : centerX(centerX), centerY(centerY), color(color) {}
    virtual ~Shape() = default;

    virtual double getArea() = 0;
    virtual double getPerimeter() = 0;
    virtual double getWidth() = 0;
    virtual double getHeight() = 0;
    virtual void setColor(Color color) { this->color = color; }
    virtual Color getColor() const { return color; }
    virtual void setCenter(double x, double y) { centerX = x; centerY = y; }
    virtual void showInfo() const {
        std::cout << "Фигура: " << getDescription() << std::endl;
        std::cout << "Цвет: " << getColor() << std::endl;
        std::cout << "Центр: (" << centerX << ", " << centerY << ")" << std::endl;
        std::cout << "Площадь: " << getArea() << std::endl;
        std::cout << "Периметр: " << getPerimeter() << std::endl;
        std::cout << "Ширина: " << getWidth() << std::endl;
        std::cout << "Высота: " << getHeight() << std::endl;
    }

    virtual std::string getDescription() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double centerX, double centerY, double radius, Color color) : Shape(centerX, centerY, color), radius(radius) {}

    double getArea() override { return M_PI * pow(radius, 2); }
    double getPerimeter() override { return 2 * M_PI * radius; }
    double getWidth() override { return 2 * radius; }
    double getHeight() override { return 2 * radius; }
    std::string getDescription() const override { return "круг"; }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double centerX, double centerY, double side, Color color) : Shape(centerX, centerY, color), side(side) {}

    double getArea() override { return pow(side, 2); }
    double getPerimeter() override { return 4 * side; }
    double getWidth() override { return 2 * side; }
    double getHeight() override { return 2 * side; }
    std::string getDescription() const override { return "квадрат"; }
};

class EquilateralTriangle : public Shape {
private:
    double side;

public:
    EquilateralTriangle(double centerX, double centerY, double side, Color color) : Shape(centerX, centerY, color), side(side) {}

    double getArea() override { return side * side * sqrt(3) / 4; }
    double getPerimeter() override { return 3 * side; }
    double getWidth() override { return 2 * side; }
    double getHeight() override { return 2 * side * sqrt(3) / 2; }
    std::string getDescription() const override { return "равносторонний треугольник"; }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double centerX, double centerY, double width, double height, Color color) : Shape(centerX, centerY, color), width(width), height(height) {}

    double getArea() override { return width * height; }
    double getPerimeter() override { return 2 * (width + height); }
    double getWidth() override { return width; }
    double getHeight() override { return height; }
    std::string getDescription() const override { return "прямоугольник"; }
};
//task3
class Employee {
public:
    std::string name;
    int teamId;
    int level;
    int assignedTasks;

    Employee(std::string name, int teamId, int level)
        : name(name), teamId(teamId), level(level), assignedTasks(0) {}

    void assignTask(int taskId) {
        std::cout << "Employee " << name << " received task " << taskId << std::endl;
        assignedTasks++;
    }

    void reportWork() {
        std::cout << "Employee " << name << " finished all assigned tasks." << std::endl;
    }
};

class Team {
public:
    std::string name;
    std::vector<Employee> employees;
    std::map<int, int> tasksAssigned;

    Team(std::string name) : name(name) {}

    void receiveTask(int taskId) {
        int randomTaskNum = rand() % employees.size();
        if (tasksAssigned.find(randomTaskNum) == tasksAssigned.end()) {
            employees[randomTaskNum].assignTask(taskId);
            tasksAssigned[randomTaskNum] = taskId;
        } else {
            receiveTask(taskId);
        }
    }

    void reportAllWorkers() {
        for (const auto& employee : employees) {
            if (employee.assignedTasks == 0) {
                std::cout << "Team " << name << " has unoccupied worker " << employee.name << std::endl;
            }
        }
    }
};

class Company {
public:
    std::string companyName;
    std::vector<Team> teams;

    Company(std::string companyName) : companyName(companyName) {}

    void processCommands(int commands) {
        std::cout << "Company " << companyName << " started processing commands..." << std::endl;
        for (int i = 0; i < commands; i++) {
            int commandId = rand() % teams.size();
            teams[commandId].receiveTask(i);
        }
        std::cout << "All commands processed." << std::endl;
    }

    void reportAllTeams() {
        for (const auto& team : teams) {
            team.reportAllWorkers();
        }
    }
};

#endif // LESSON9_H
