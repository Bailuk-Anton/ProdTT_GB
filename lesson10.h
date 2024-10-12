#ifndef LESSON10_H
#define LESSON10_H
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


class Lesson10
{
    void task1();
    void task2();
    void task3();
public:
    Lesson10();
};
//task1
class Swimmer {
public:
    std::string name;
    double speed;

    Swimmer(std::string name, double speed) : name(name), speed(speed) {}

    void swim() {
        std::cout << "Стартовал " << name << std::endl;
        for (int i = 0; i < 100; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / speed)));
            std::cout << name << " проплыл " << i + 1 << " м." << std::endl;
        }
        std::cout << name << " финишировал." << std::endl;
    }
};
//task2
class Train {
public:
    char trainCode;
    unsigned int arrivalTime;
    bool arrivedAtStation;
    std::mutex mutex;
    std::condition_variable condVar;

    Train(char code, unsigned int time) : trainCode(code), arrivalTime(time), arrivedAtStation(false) {}

    void arriveAtStation() {
        std::unique_lock<std::mutex> lock(mutex);
        arrivedAtStation = true;
        condVar.notify_one();
    }

    void leaveStation() {
        std::unique_lock<std::mutex> lock(mutex);
        arrivedAtStation = false;
        condVar.notify_one();
    }

    void waitToDepart() {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this] { return !arrivedAtStation; });
    }

    void goToStation() {
        std::this_thread::sleep_for(std::chrono::seconds(arrivalTime));
        arriveAtStation();
    }
};

class Station {
public:
    std::mutex stationMutex;
    std::condition_variable stationCondVar;
    std::queue<Train*> waitingTrains;
    Train* currentTrain;

    Station() : currentTrain(nullptr) {}

    void checkInTrain(Train* train) {
        std::unique_lock<std::mutex> lock(stationMutex);
        if (currentTrain == nullptr) {
            currentTrain = train;
            train->leaveStation();
        } else {
            waitingTrains.push(train);
            std::cout << "Поезд " << train->trainCode << " прибыл, ожидает на платформе." << std::endl;
        }
    }

    void releasePlatform() {
        std::unique_lock<std::mutex> lock(stationMutex);
        if (waitingTrains.size() > 0) {
            currentTrain = waitingTrains.front();
            waitingTrains.pop();
            currentTrain->leaveStation();
        } else {
            currentTrain = nullptr;
        }
    }

    void departTrain(Train* train) {
        std::unique_lock<std::mutex> lock(stationMutex);
        if (currentTrain == train) {
            currentTrain = nullptr;
            std::cout << "Поезд " << train->trainCode << " отправился." << std::endl;
        } else {
            std::cout << "Поезд " << train->trainCode << " уже не на станции." << std::endl;
        }
    }
};
//task3
enum class MenuItem { Pizza, Soup, Steak, Salad, Sushi };

class Order {
public:
    MenuItem item;
    std::mutex orderMutex;
    std::condition_variable orderCondVar;

    Order(MenuItem item) : item(item) {}

    void readyToPickup() {
        std::unique_lock<std::mutex> lock(orderMutex);
        orderCondVar.notify_all();
    }

    void waitForReady() {
        std::unique_lock<std::mutex> lock(orderMutex);
        orderCondVar.wait(lock, [this] { return true; });
    }
};

class Kitchen {
public:
    std::queue<Order*> orders;
    std::mutex kitchenMutex;
    std::condition_variable kitchenCondVar;

    void cook(Order* order) {
        std::unique_lock<std::mutex> lock(kitchenMutex);
        orders.push(order);
        kitchenCondVar.notify_one();
    }

    void prepareAndCook() {
        std::unique_lock<std::mutex> lock(kitchenMutex);
        if (orders.size() > 0) {
            Order* order = orders.front();
            orders.pop();
            std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 10 + 5));
            order->readyToPickup();
        } else {
            kitchenCondVar.wait(lock, [this] { return orders.size() > 0; });
        }
    }
};

class Courier {
public:
    std::mutex courierMutex;
    std::condition_variable courierCondVar;
    std::queue<Order*> readyOrders;

    void pickUpOrders() {
        std::unique_lock<std::mutex> lock(courierMutex);
        if (readyOrders.size() > 0) {
            Order* order = readyOrders.front();
            readyOrders.pop();
            std::cout << "Заказ " << order->item << " доставлен." << std::endl;
        } else {
            courierCondVar.wait(lock, [this] { return readyOrders.size() > 0; });
        }
    }
};

#endif // LESSON10_H
