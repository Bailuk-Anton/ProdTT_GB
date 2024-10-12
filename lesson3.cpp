#include "lesson3.h"

void validateDate(const std::string& dateString) {
    static const std::string allowedCharacters = "0123456789.";
    if (dateString.size() != 10 || !std::all_of(dateString.begin(), dateString.end(), [](char c) { return allowedCharacters.find(c) != std::string::npos; })) {
        throw std::invalid_argument("Invalid date format. Expected DD.MM.YYYY.");
    }
}
void Lesson3::task1()
{
    std::string command;
    std::string filename = "payments.txt";

    PaymentBook book(filename);
    book.readPayments();

    while (true) {
        std::cout << "Enter command (list / add): ";
        std::getline(std::cin, command);

        if (command == "list") {
            book.listPayments();
        } else if (command == "add") {
            std::cout << "Enter name: ";
            std::string name;
            std::getline(std::cin, name);

            std::cout << "Enter surname: ";
            std::string surname;
            std::getline(std::cin, surname);

            std::cout << "Enter date (DD.MM.YYYY): ";
            std::string dateString;
            std::getline(std::cin, dateString);
            validateDate(dateString);

            std::cout << "Enter amount: ";
            std::string amountStr;
            std::getline(std::cin, amountStr);
            int amount;
            try {
                amount = std::stoi(amountStr);
            } catch (...) {
                std::cerr << "Invalid amount: " << amountStr << std::endl;
                continue;
            }

            Payment p{name, surname, dateString, amount};
            book.addPayment(p);
        } else {
            std::cout << "Invalid command.\n";
        }
    }

}

void Lesson3::task2(){
    Plot plot{1, {}};
    House house{1, 100.0f, {{}, {}, {}}, {{2, 2.4f}, {3, 2.5f}}};
    Garage garage{2, 30.0f};
    Shed shed{3, 20.0f};
    Bathhouse bathhouse{4, 50.0f, {5.0f, 2.0f}};

    plot.buildings.push_back(house);
    plot.buildings.push_back(garage);
    plot.buildings.push_back(shed);
    plot.buildings.push_back(bathhouse);

    std::cout << "Plot ID: " << plot.id << std::endl;
    std::cout << "House info:" << std::endl;
    std::cout << "ID: " << house.id << ", Area: " << house.area << std::endl;
    std::cout << "Rooms:" << std::endl;
    for (const auto& room : house.rooms) {
        std::cout << "Type: " << room.type << ", Area: " << room.area << std::endl;
    }
    std::cout << "Floors:" << std::endl;
    for (const auto& floor : house.floors) {
        std::cout << "Number of Rooms: " << floor.num_rooms << ", Ceiling Height: " << floor.ceiling_height << std::endl;
    }
    std::cout << "Bathhouse info:" << std::endl;
    std::cout << "ID: " << bathhouse.id << ", Area: " << bathhouse.area << std::endl;
    std::cout << "Pipe info:" << std::endl;
    std::cout << "Diameter: " << bathhouse.pipe.diameter << ", Length: " << bathhouse.pipe.length << std::endl;

}

void Lesson3::task3()
{
    std::string command;
    std::cout << "Enter command (add, subtract, scale, length, normalize): ";
    std::getline(std::cin, command);

    Vector2D u, v;
    double scalar;

    if (command == "add") {
        std::cout << "Enter vector u: ";
        std::getline(std::cin, command);
        std::stringstream ss(command);
        ss >> u.x >> u.y;

        std::cout << "Enter vector v: ";
        std::getline(std::cin, command);
        ss.str(command);
        ss >> v.x >> v.y;

        Vector2D result = add(u, v);
        std::cout << "Result: " << result << std::endl;
    } else if (command == "subtract") {
        std::cout << "Enter vector u: ";
        std::getline(std::cin, command);
        std::stringstream ss(command);
        ss >> u.x >> u.y;

        std::cout << "Enter vector v: ";
        std::getline(std::cin, command);
        ss.str(command);
        ss >> v.x >> v.y;

        Vector2D result = subtract(u, v);
        std::cout << "Result: " << result << std::endl;
    } else if (command == "scale") {
        std::cout << "Enter vector v: ";
        std::getline(std::cin, command);
        std::stringstream ss(command);
        ss >> v.x >> v.y;

        std::cout << "Enter scalar: ";
        std::getline(std::cin, command);
        scalar = std::stod(command);

        Vector2D result = scale(v, scalar);
        std::cout << "Result: " << result << std::endl;
    } else if (command == "length") {
        std::cout << "Enter vector v: ";
        std::getline(std::cin, command);
        std::stringstream ss(command);
        ss >> v.x >> v.y;

        double result = length(v);
        std::cout << "Length: " << result << std::endl;
    } else if (command == "normalize") {
        std::cout << "Enter vector v: ";
        std::getline(std::cin, command);
        std::stringstream ss(command);
        ss >> v.x >> v.y;

        Vector2D result = normalize(v);
        std::cout << "Normalized vector: " << result << std::endl;
    } else {
        std::cout << "Invalid command." << std::endl;
    }
}


Lesson3::Lesson3()
{

}
