#include "lesson2.h"

void addNewRecordToFile(const std::string& filename, const std::string& record) {
    std::ofstream outputFile(filename, std::ios::app);
    if (outputFile) {
        outputFile << record << '\n';
        outputFile.close();
    } else {
        std::cerr << "Failed to append data to file: " << filename << std::endl;
    }
}

void validateDate(const std::string& dateString) {
    static const std::string allowedCharacters = "0123456789.";
    if (dateString.size() != 10 || !std::all_of(dateString.begin(), dateString.end(), [](char c) { return allowedCharacters.find(c) != std::string::npos; })) {
        throw std::invalid_argument("Invalid date format. Expected DD.MM.YYYY.");
    }
}

void Lesson2::task1()
{
    std::string filename = "payments.txt";
    std::string record;

    while (true) {
        std::cout << "Enter recipient name: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Enter recipient surname: ";
        std::string surname;
        std::getline(std::cin, surname);

        std::cout << "Enter payment date (DD.MM.YYYY): ";
        std::string dateString;
        std::getline(std::cin, dateString);
        validateDate(dateString);

        std::cout << "Enter payment amount: ";
        std::string amount;
        std::getline(std::cin, amount);

        std::ostringstream oss;
        oss << name << " " << surname << " " << dateString << " " << amount;
        record = oss.str();

        addNewRecordToFile(filename, record);

        std::cout << "Would you like to enter another record? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'n') {
            break;
        }
    }
}

void Lesson2::task2(){
    // Включение поддержки C++11
    std::default_random_engine generator;

    // Получение размеров изображения от пользователя
    int width, height;
    std::cout << "Enter the width of the picture: ";
    std::cin >> width;
    std::cout << "Enter the height of the picture: ";
    std::cin >> height;

    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr));

    // Генерация случайных чисел для каждого пикселя
    std::uniform_int_distribution<int> distribution(0, 1);

    // Открытие файла для записи
    std::ofstream outFile("pic.txt");
    if (!outFile) {
        std::cerr << "Error opening file 'pic.txt'" << std::endl;
        return 1;
    }

    // Рисование картинки
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            outFile << distribution(generator);
        }
        outFile << '\n';
    }

    // Закрытие файла
    outFile.close();

    std::cout << "Generated random picture with dimensions " << width << "x" << height << " has been saved to 'pic.txt'" << std::endl;

}

void Lesson2::task3(){
    std::ifstream riverFile("river.txt");
    if (!riverFile) {
        std::cerr << "Could not open file: river.txt" << std::endl;
        return;
    }

    std::ofstream basketFile("basket.txt", std::ios::app);
    if (!basketFile) {
        std::cerr << "Could not open file: basket.txt" << std::endl;
        return;
    }

    std::vector<std::string> fishList;
    std::string fish;
    while (riverFile >> fish) {
        fishList.push_back(fish);
    }
    riverFile.close();

    std::string targetFish;
    std::cout << "Enter type of fish you want to catch: ";
    std::getline(std::cin, targetFish);

    int caughtCount = 0;
    for (const auto& f : fishList) {
        if (targetFish == f) {
            basketFile << f << '\n';
            caughtCount++;
        }
    }

    std::cout << "Caught " << caughtCount << " fish." << std::endl;
}

void Lesson2::task4(){
    std::string stateFilePath = "bankomat_state.bin";
    ATM atm(stateFilePath);

    char operation;
    std::cout << "Enter operation (+ for filling or - for withdrawal): ";
    std::cin >> operation;

    switch (operation) {
        case '+':
            atm.fill();
            break;
        case '-': {
            int amount;
            std::cout << "Enter amount to withdraw (in hundreds of rubles): ";
            std::cin >> amount;
            atm.withdraw(amount * 100);
            break;
        }
        default:
            std::cerr << "Invalid operation." << std::endl;
            break;
    }
}


Lesson2::Lesson2()
{

}
