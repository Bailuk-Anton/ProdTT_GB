#include "lesson4.h"

using namespace std;

typedef map<string, vector<string>> Phonebook;

Phonebook phonebook;

void addEntry(const string& number, const string& lastname) {
    phonebook[lastname].push_back(number);
}

vector<string> findNumbersByLastname(const string& lastname) {
    return phonebook[lastname];
}

string findLastnameByNumber(const string& number) {
    for (const auto& kvp : phonebook) {
        for (const auto& n : kvp.second) {
            if (n == number) {
                return kvp.first;
            }
        }
    }
    return "";
}

void Lesson4::task1()
{
    string query;
    while (true) {
        cout << "Enter query (format: number-lastname / number / lastname): ";
        getline(cin, query);
        if (query == "exit") {
            break;
        }

        size_t dashIndex = query.find('-');
        if (dashIndex != string::npos) {
            // Add entry
            string number = query.substr(0, dashIndex);
            string lastname = query.substr(dashIndex + 1);
            addEntry(number, lastname);
        } else if (query.find(' ') != string::npos) {
            // Find lastname by number
            string number = query;
            string lastname = findLastnameByNumber(number);
            if (!lastname.empty()) {
                cout << lastname << endl;
            } else {
                cout << "No such number found." << endl;
            }
        } else {
            // Find numbers by lastname
            string lastname = query;
            vector<string> numbers = findNumbersByLastname(lastname);
            if (numbers.empty()) {
                cout << "No such lastname found." << endl;
            } else {
                for (const auto& number : numbers) {
                    cout << number << " ";
                }
                cout << endl;
            }
        }
    }
}

typedef multimap<string, string> Registry;
Registry registry;

void enqueuePatient(const string& patient) {
    registry.insert({patient, ""});
}

string dequeuePatient() {
    queue<pair<string, string>> patients;
    for (const auto& kvp : registry) {
        patients.push(kvp);
    }
    string firstPatient = patients.front().first;
    registry.erase(firstPatient);
    return firstPatient;
}

void Lesson4::task2(){
    string query;
    while (true) {
        cout << "Enter query (Next / Patient Name): ";
        getline(cin, query);
        if (query == "exit") {
            break;
        }

        if (query == "Next") {
            string nextPatient = dequeuePatient();
            cout << "Calling " << nextPatient << endl;
        } else {
            enqueuePatient(query);
        }
    }
}

bool areAnagrams(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) {
        return false;
    }

    std::map<char, int> letterCount;

    for (char c : s1) {
        letterCount[c]++;
    }

    for (char c : s2) {
        if (letterCount.find(c) == letterCount.end()) {
            return false;
        } else {
            letterCount[c]--;
            if (letterCount[c] == 0) {
                letterCount.erase(c);
            }
        }
    }

    return letterCount.empty();
}

void Lesson4::task3(){
    std::string s1 = "лекарство";
    std::string s2 = "стекловар";

    if (areAnagrams(s1, s2)) {
        std::cout << "Strings are anagrams." << std::endl;
    } else {
        std::cout << "Strings are not anagrams." << std::endl;
    }

}

Lesson4::Lesson4()
{

}
