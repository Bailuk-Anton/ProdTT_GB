#include "lesson8.h"

using namespace std;

void Lesson8::task1()
{
    Player player;

    Track track1("Song 1", {1, 1, 2022, 0, 0, 0}, 120);
    Track track2("Song 2", {1, 1, 2022, 0, 0, 0}, 180);
    Track track3("Song 3", {1, 1, 2022, 0, 0, 0}, 240);

    player.addTrack(track1);
    player.addTrack(track2);
    player.addTrack(track3);

    while (true) {
        cout << ">";
        string command;
        getline(cin, command);

        if (command == "play") {
            string title;
            cout << "Enter track title: ";
            getline(cin, title);
            player.playTrack(title);
        } else if (command == "pause") {
            player.pause();
        } else if (command == "resume") {
            player.resume();
        } else if (command == "next") {
            player.nextTrack();
        } else if (command == "stop") {
            player.stop();
        } else if (command == "exit") {
            player.clearTracks();
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }
}

void Lesson8::task2(){
    Phone phone;

    while (true) {
        cout << ">";
        string command;
        getline(cin, command);

        if (command == "add") {
            string name;
            cout << "Enter contact name: ";
            getline(cin, name);
            string phoneNumber;
            cout << "Enter contact phone number (+7 <10 digits>): ";
            getline(cin, phoneNumber);
            phone.addContact(name, phoneNumber);
        } else if (command == "call") {
            string contactNameOrNumber;
            cout << "Enter contact name or phone number: ";
            getline(cin, contactNameOrNumber);
            phone.call(contactNameOrNumber);
        } else if (command == "sms") {
            string contactNameOrNumber;
            cout << "Enter contact name or phone number: ";
            getline(cin, contactNameOrNumber);
            string message;
            cout << "Enter message: ";
            getline(cin, message);
            phone.sendSMS(contactNameOrNumber, message);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }
}

void Lesson8::task3(){
    Screen screen(80, 50);
    Window window(0, 0, 10, 10);

    screen.drawWindow(window);
    screen.draw();

    while (true) {
        std::cout << ">";
        std::string command;
        std::getline(std::cin, command);

        if (command == "move") {
            int dx, dy;
            std::cout << "Enter delta x and y separated by space: ";
            std::cin >> dx >> dy;
            std::vector<int> delta{dx, dy};
            window.move(delta);
        } else if (command == "resize") {
            int newWidth, newHeight;
            std::cout << "Enter new width and height separated by space: ";
            std::cin >> newWidth >> newHeight;
            std::vector<int> newSize{newWidth, newHeight};
            window.resize(newSize);
        } else if (command == "display") {
            screen.drawWindow(window);
            screen.draw();
        } else if (command == "close") {
            screen.eraseWindow(window);
            screen.draw();
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }
}

Lesson8::Lesson8()
{

}
