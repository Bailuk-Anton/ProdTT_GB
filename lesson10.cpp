#include "lesson10.h"

void Lesson10::task1(){
    std::vector<Swimmer> swimmers;

    std::cout << "Введите имена пловцов (разделяя пробелом): ";
    std::string names;
    std::getline(std::cin, names);
    std::stringstream ss(names);

    std::cout << "Введите скорости пловцов (разделяя пробелом): ";
    std::string speeds;
    std::getline(std::cin, speeds);
    std::stringstream ss2(speeds);

    std::string name;
    double speed;
    while (ss >> name) {
        if (ss2 >> speed) {
            swimmers.push_back(Swimmer(name, speed));
        } else {
            std::cout << "Ошибка ввода скоростей, пропускаем пловца." << std::endl;
        }
    }

    std::vector<std::thread> threads;
    for (const auto& swimmer : swimmers) {
        threads.push_back(std::thread(&Swimmer::swim, swimmer));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::sort(swimmers.begin(), swimmers.end(), [](const Swimmer& a, const Swimmer& b) {
        return a.speed > b.speed;
    });

    std::cout << "РЕЗУЛЬТАТЫ ЗАПЛЫВА:\n";
    for (const auto& swimmer : swimmers) {
        std::cout << swimmer.name << " - " << swimmer.speed << " м/с" << std::endl;
    }

}

void Lesson10::task2(){
    Station station;

    char trainCode;
    unsigned int travelTime;

    std::cout << "Введите время в пути для поезда A: ";
    std::cin >> trainCode >> travelTime;
    Train* trainA = new Train(trainCode, travelTime);

    std::cout << "Введите время в пути для поезда B: ";
    std::cin >> trainCode >> travelTime;
    Train* trainB = new Train(trainCode, travelTime);

    std::cout << "Введите время в пути для поезда C: ";
    std::cin >> trainCode >> travelTime;
    Train* trainC = new Train(trainCode, travelTime);

    std::thread thA(Train::goToStation, trainA);
    std::thread thB(Train::goToStation, trainB);
    std::thread thC(Train::goToStation, trainC);

    thA.join();
    thB.join();
    thC.join();

    while (true) {
        char command;
        std::cout << "> ";
        std::cin >> command;
        switch (command) {
            case 'd':
                station.departTrain(trainA);
                break;
            case 'a':
                station.checkInTrain(trainA);
                break;
            case 'b':
                station.checkInTrain(trainB);
                break;
            case 'c':
                station.checkInTrain(trainC);
                break;
            case 'q':
                std::cout << "Программа завершена." << std::endl;
                return 0;
            default:
                std::cout << "Неизвестная команда." << std::endl;
        }
    }
}

void Lesson10::task3(){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(5, 10);

    Kitchen kitchen;
    Courier courier;

    std::thread kitchenThread(&Kitchen::prepareAndCook, &kitchen);
    std::thread courierThread(&Courier::pickUpOrders, &courier);

    std::cout << "Онлайн-ресторан начал работу." << std::endl;

    while (true) {
        MenuItem menuItem = static_cast<MenuItem>(generator() % 5);
        std::cout << "Поступил заказ: " << menuItem << std::endl;

        Order* order = new Order(menuItem);
        std::this_thread::sleep_for(std::chrono::seconds(distribution(generator)));
        kitchen.cook(order);

        std::this_thread::sleep_for(std::chrono::seconds(distribution(generator)));
        order->waitForReady();

        std::this_thread::sleep_for(std::chrono::seconds(30));
        courier.readyOrders.push(order);

        if (courier.readyOrders.size() >= 10) {
            std::cout << "Ресторан успешно завершил 10 доставок." << std::endl;
            break;
        }
    }

    kitchenThread.join();
    courierThread.join();

}


Lesson10::Lesson10()
{

}
