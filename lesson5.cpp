#include "lesson5.h"

#define STRINGIFY(s) #s
#define TO_STRING(s) STRINGIFY(s)

#define MONDAY "Monday"
#define TUESDAY "Tuesday"
#define WEDNESDAY "Wednesday"
#define THURSDAY "Thursday"
#define FRIDAY "Friday"
#define SATURDAY "Saturday"
#define SUNDAY "Sunday"

#ifdef SPRING
#define SEASON "Spring"
#elif defined(SUMMER)
#define SEASON "Summer"
#elif defined(AUTUMN)
#define SEASON "Autumn"
#elif defined(WINTER)
#define SEASON "Winter"
#else
#error No season selected
#endif

#define DAYS_OF_WEEK \
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY

#define IS_VALID_DAY(day) \
    (day >= 0 && day <= 6)

#define GET_DAY_NAME(day) \
    DAYS_OF_WEEK[day]

define PRINT_IF_OVERFLOW(arr, idx, condition) { \
    if (condition) { \
        std::cout << "Overfull car " << idx << std::endl; \
    } \
}

#define PRINT_IF_UNDERFLOW(arr, idx, condition) { \
    if (condition) { \
        std::cout << "Underfull car " << idx << std::endl; \
    } \
}

#define FOR_EACH_CAR(idx, arr) \
    for (size_t idx = 0; idx < arr.size(); ++idx)

#define CHECK_AND_PRINT_CARS(arr) \
    FOR_EACH_CAR(idx, arr) { \
        int passengers = arr[idx]; \
        PRINT_IF_OVERFLOW(arr, idx, passengers > 20); \
        PRINT_IF_UNDERFLOW(arr, idx, passengers == 0); \
    }

void Lesson5::task1()
{
    int day;
    std::cout << "Enter the day of week as a number: ";
    std::cin >> day;

    if (IS_VALID_DAY(day)) {
        std::cout << TO_STRING(GET_DAY_NAME(day)) << std::endl;
    } else {

    }
}

void Lesson5::task2()
{
    std::cout << SEASON << std::endl;
}

void printTotalPassengers(const std::vector<int>& cars) {
    int total = 0;
    FOR_EACH_CAR(idx, cars) {
        total += cars[idx];
    }
    std::cout << "Total passengers: " << total << std::endl;
}

void Lesson5::task3()
{
    std::vector<int> cars(10);
    FOR_EACH_CAR(idx, cars) {
        std::cout << "Enter number of passengers in car " << idx << ": ";
        std::cin >> cars[idx];
    }

    CHECK_AND_PRINT_CARS(cars);
    printTotalPassengers(cars);
}

Lesson5::Lesson5()
{

}
