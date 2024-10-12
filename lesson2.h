#ifndef LESSON2_H
#define LESSON2_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <cassert>

class Lesson2
{
    void task1();
    void task2();
    void task3();
    void task4();
    void task5();
public:
    Lesson2();
    static void run();
};

enum class Operation { Fill, Withdraw };

class ATM {
public:
    explicit ATM(const std::string& stateFilePath) : stateFilePath(stateFilePath) {}

    void initializeStateFromFile() {
        loadStateFromFile();
    }

    void saveStateToFile() {
        storeStateToFile();
    }

    void fill() {
        generateRandomNotes();
        saveStateToFile();
    }

    void withdraw(int amount) {
        assert(amount <= totalAmount());
        removeNotes(amount);
        saveStateToFile();
    }

private:
    std::string stateFilePath;
    std::vector<int> notes;

    void loadStateFromFile() {
        std::ifstream inputFile(stateFilePath, std::ios::binary);
        if (!inputFile) {
            std::cerr << "Error opening file: " << stateFilePath << std::endl;
            return;
        }

        inputFile.read(reinterpret_cast<char*>(notes.data()), notes.size() * sizeof(int));
        inputFile.close();
    }

    void storeStateToFile() {
        std::ofstream outputFile(stateFilePath, std::ios::binary);
        if (!outputFile) {
            std::cerr << "Error opening file: " << stateFilePath << std::endl;
            return;
        }

        outputFile.write(reinterpret_cast<const char*>(notes.data()), notes.size() * sizeof(int));
        outputFile.close();
    }

    void generateRandomNotes() {
        notes.clear();
        int maxCapacity = 1000;
        int minValue = 100;
        int maxValue = 5000;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minValue, maxValue);

        while (notes.size() < maxCapacity) {
            int value = dis(gen);
            notes.push_back(value);
        }
    }

    int totalAmount() const {
        int total = 0;
        for (auto note : notes) {
            total += note;
        }
        return total;
    }

    void removeNotes(int amount) {
        for (int i = 0; (i < notes.size()) && (amount > 0); ++i) {
            if (notes[i] <= amount) {
                notes[i] = 0;
                amount -= notes[i];
            } else {
                notes[i] -= amount;
                amount = 0;
            }
        }
    }
};


#endif // LESSON2_H
