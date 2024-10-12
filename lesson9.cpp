#include "lesson9.h"

void Lesson9::task1()
{
    std::vector<Tree> trees;
    for (int i = 0; i < 5; ++i) {
        Tree tree(3, 2);
        tree.generate_tree();
        for (int j = 0; j < tree.homes.size(); ++j) {
            tree.assign_elf(j);
        }
        trees.push_back(tree);
    }

    std::string elf_name = get_user_input();
    for (const auto& tree : trees) {
        int neighbours = tree.count_neighbours(elf_name);
        if (neighbours > 0) {
            std::cout << "Elf '" << elf_name << "' has " << neighbours << " neighbours." << std::endl;
            break;
        }
    }
}

void Lesson9::task2(){
    Circle circle(0, 0, 5, Red);
    circle.showInfo();

    Square square(10, 10, 5, Blue);
    square.showInfo();

    EquilateralTriangle triangle(20, 20, 5, Green);
    triangle.showInfo();

    Rectangle rectangle(30, 30, 10, 5, None);
    rectangle.showInfo();
}

void Lesson9::task3(){
    std::cout << "Welcome to the company simulation!\n";

    std::string companyName;
    std::cout << "Enter company name: ";
    std::getline(std::cin, companyName);

    Company company(companyName);

    int numTeams;
    std::cout << "Enter number of teams: ";
    std::cin >> numTeams;

    int numEmployeesPerTeam;
    std::cout << "Enter number of employees per team: ";
    std::cin >> numEmployeesPerTeam;

    for (int i = 0; i < numTeams; i++) {
        std::string teamName;
        std::cout << "Enter team " << i + 1 << " name: ";
        std::getline(std::cin, teamName);

        for (int j = 0; j < numEmployeesPerTeam; j++) {
            std::string employeeName;
            std::cout << "Enter employee " << j + 1 << " name: ";
            std::getline(std::cin, employeeName);

            int teamId = i;
            int level = j;
            Employee employee(employeeName, teamId, level);
            teams[i].employees.push_back(employee);
        }
    }

    int commands;
    std::cout << "Enter number of commands from CEO: ";
    std::cin >> commands;

    std::srand(commands);

    company.processCommands(commands);
    company.reportAllTeams();
}

Lesson9::Lesson9()
{

}
