#include "lesson1.h"

void Lesson1::task1()
{
    // Имя файла
        const std::string file_name = "words.txt";

        // Искомое слово
        std::string search_word;
        std::cout << "Enter the word to search for: ";
        std::cin >> search_word;

        // Чтение содержимого файла
        std::ifstream input_file(file_name);
        if (!input_file) {
            std::cerr << "Error opening file '" << file_name << "'." << std::endl;
            return 1;
        }

        std::vector<std::string> words;
        std::string line;
        while (getline(input_file, line)) {
            std::istringstream ss(line);

            std::string word;
            while (ss >> word) {
                words.push_back(word);
            }
        }

        // Закрытие файла
        input_file.close();

        int count = 0;
        for (const auto& w : words) {
            if (w == search_word) {
                ++count;
            }
        }

        // Вывод результата
        if (count > 0) {
            std::cout << "Word \"" << search_word << "\" occurs " << count << " times." << std::endl;
        } else {
            std::cout << "Word \"" << search_word << "\" does not occur in the file." << std::endl;
        }
}

void Lesson1::task2(){
    // Запрашиваем путь к файлу
        std::string filePath;
        std::cout << "Enter path to text file: ";
        std::getline(std::cin, filePath);

        // Открываем файл для чтения
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "File could not be opened: " << filePath << std::endl;
            return 1;
        }

        // Читаем каждую строку из файла и выводим её
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }

        // Закрываем файл
        file.close();
}

struct PaymentRecord {
    std::string name;
    double amount;
    std::string date;
};

void printPayments(const std::vector<PaymentRecord>& payments) {
    for (const auto& payment : payments) {
        std::cout << payment.name << payment.amount << " " << payment.date << "\n";
    }
}

double getTotalAmount(const std::vector<PaymentRecord>& payments) {
    double totalAmount = 0.0;
    for (const auto& payment : payments) {
        totalAmount += payment.amount;
    }
    return totalAmount;
}

std::string findMaxPayer(const std::vector<PaymentRecord>& payments) {
    double maxAmount = 0.0;
    std::string maxName;
    for (const auto& payment : payments) {
        if (payment.amount > maxAmount) {
            maxAmount = payment.amount;
            maxName = payment.name;
        }
    }
    return maxName;
}

void Lesson1::task3(){
    std::ifstream inputFile("payments.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file 'payments.txt'\n";
        return 1;
    }

    std::vector<PaymentRecord> payments;
    std::string line;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string name;
        double amount;
        std::string date;
        ss >> name >> amount >> date;
        payments.emplace_back(PaymentRecord{name, amount, date});
    }

    double totalAmount = getTotalAmount(payments);
    std::cout << "Total amount paid: $" << totalAmount << "\n\n";

    std::string maxPayer = findMaxPayer(payments);
    std::cout << "Person with maximum payments: " << maxPayer << "\n";

    printPayments(payments);

}

// Константы для проверки первых четырех байт заголовка PNG
constexpr char SIGNATURE[] = {-119, 'P', 'N', 'G'};

bool isValidPngHeader(const unsigned char* header) {
    return memcmp(header, SIGNATURE, sizeof(SIGNATURE)) == 0;
}

void Lesson1::task4(){
    // Получение пути к файлу от пользователя
    std::string filePath;
    std::cout << "Enter path to file: ";
    std::getline(std::cin, filePath);

    // Открытие файла в бинарном режиме
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return 1;
    }

    // Проверка размера файла
    size_t fileSize = file.tellg();
    if (fileSize < sizeof(SIGNATURE)) {
        std::cerr << "File too small to contain a valid PNG signature: " << filePath << std::endl;
        return 1;
    }

    // Перемещение указателя на начало файла
    file.seekg(0);

    // Чтение первых восьми байт
    unsigned char header[sizeof(SIGNATURE)];
    file.read((char*)header, sizeof(SIGNATURE));

    // Проверка заголовка
    bool isPng = isValidPngHeader(header);

    // Закрытие файла
    file.close();

    // Вывод результата
    if (isPng) {
        std::cout << "The file is a valid PNG image: " << filePath << std::endl;
    } else {
        std::cout << "The file is NOT a valid PNG image: " << filePath << std::endl;
    }

}

// Выбор сектора
int chooseSector(int currentSector) {
    std::cout << "Выберите смещение (оффсет): ";
    int offset;
    std::cin >> offset;
    int newSector = (currentSector + offset) % 13;
    return newSector;
}

void Lesson1::task5(){

    const std::array<std::string, 13> sectors = {"Ведущий", "Кот", "Письмо", "Черный ящик", "Музыкальная пауза", "Знаменитости", "Реклама", "Вопрос телезрителей", "Блиц", "Аукцион", "Зеро", "Музей", "Риск"};

    // Карта вопросов и ответов по секторам
    std::map<std::string, std::pair<std::string, std::string>> questionsAndAnswers = {
        {"Ведущий", {"Какой предмет можно увидеть на логотипе игры?", "Нуль"} },
        {"Кот", {"Какое животное изображено на гербе Москвы?", "Кошка"} },
        {"Письмо", {"В каком городе впервые было применено колесо?", "Фивы"} },
        {"Черный ящик", {"Из чего сделаны кубики Рубика?", "Пластик"} },
        {"Музыкальная пауза", {"Какая группа играла песню Yesterday?", "The Beatles"} },
        {"Знаменитости", {"Кто изобрел автомобиль?", "<NAME>"} },
        {"Реклама", {"Кто придумал попкорн?", "Индейцы"} },
        {"Вопрос телезрителей", {"Что такое биткоин?", "Виртуальная валюта"} },
        {"Блиц", {"Какую страну называют Швейцарией Востока?", "Японию"} },
        {"Аукцион", {"Как называется символ Венеры?", "Звезда Венеры"} },
        {"Зеро", {"Как называется цветок женьшеня?", "Корень жизни"} },
        {"Музей", {"Что означает слово «робот»?", "Чешское слово для труда"} },
        {"Риск", {"Какое имя носила жена Юлия Цезаря?", "Кальпурния"} }
    };

    // Счёт очков
    int playerScore = 0;
    int audienceScore = 0;
    int currentSector = 0;
    do {
        currentSector = chooseSector(currentSector);
        cout << "Вопрос из сектора " << sectors[currentSector] << ": " << questionsAndAnswers[sectors[currentSector]].first << std::endl;
        string answer;
        cin >> answer;
        if (answer == questionsAndAnswers[sectors[currentSector]].second) {
            playerScore++;
            std::cout << "Ваш ответ верен! Ваш счет: " << playerScore << std::endl;
        } else {
            audienceScore++;
            std:;cout << "Ваш ответ неверен. Счет зрителей: " << audienceScore << std::endl;
        }
    } while ((playerScore < 6 && audienceScore < 6) || (playerScore != 6 && audienceScore != 6));
    if (playerScore >= 6) {
        std::cout << "Поздравляем, игрок выиграл!" << std::endl;
    } else {
        std::cout << "Поздравляем, зрители выиграли!" << std::endl;
    }
}

Lesson1::Lesson1()
{

}

Lesson1::run(){
    char h;
    std::cout<<"Введите номер заддания: ";
    std::cin>>h;
    while(true){
        if(h=='1'){
            task1();
            std::cout<<"Введите любой символ для продолжения";
            std::cin>>h;
            system("clear");
        }
        if(h=='2'){
            task2();
            std::cout<<"Введите любой символ для продолжения";
            std::cin>>h;
            system("clear");
        }
        if(h=='3'){
            task3();
            std::cout<<"Введите любой символ для продолжения";
            std::cin>>h;
            system("clear");
        }
        if(h=='4'){
            task1();
            std::cout<<"Введите любой символ для продолжения";
            std::cin>>h;
            system("clear");
        }
        if(h=='5'){
            task1();
            std::cout<<"Введите любой символ для продолжения";
            std::cin>>h;
            system("clear");
        }
        if((h == 'e')&&((h == 'E')))break;
        std::cout<<"Введите номер заддания(Для выхода нажмите e): ";
        std::cin>>h;
    }


}
