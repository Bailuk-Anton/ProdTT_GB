#include "lesson6.h"


struct BirthdayData {
    std::string name;
    std::tm birthday;
};

int daysSinceEpoch(const std::tm& tm) {
    time_t t = mktime(&tm);
    return static_cast<int>(t - 0) / 86400;
}

bool operator<(const BirthdayData& lhs, const BirthdayData& rhs) {
    return daysSinceEpoch(lhs.birthday) < daysSinceEpoch(rhs.birthday);
}

void Lesson6::task2()
{
    std::vector<BirthdayData> birthdays;

    std::string name;
    while (true) {
        std::cout << "Enter name or \"end\": ";
        std::getline(std::cin, name);
        if (name == "end") {
            break;
        }

        std::cout << "Enter birthday (yyyy/mm/dd): ";
        std::string birthdayStr;
        std::getline(std::cin, birthdayStr);

        std::tm birthday;
        birthday.tm_year = std::stoi(birthdayStr.substr(0, 4)) - 1900;
        birthday.tm_mon = std::stoi(birthdayStr.substr(5, 2)) - 1;
        birthday.tm_mday = std::stoi(birthdayStr.substr(8, 2));

        birthdays.push_back({name, birthday});
    }

    // Sort birthdays by closest to today
    std::sort(birthdays.begin(), birthdays.end());

    std::tm now = std::localtime(&std::time(nullptr))->tm_localtime;
    int currentDayOfYear = now.tm_yday;

    for (const auto& bd : birthdays) {
        if (bd.birthday.tm_yday <= currentDayOfYear) {
            continue;
        }

        std::cout << bd.name << " - " << std::asctime(&bd.birthday) << std::endl;
    }
}

void Lesson6::task3(){

}

Lesson6::Lesson6()
{

}
