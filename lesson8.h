#ifndef LESSON8_H
#define LESSON8_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <map>

using namespace std;

class Lesson8
{
    void task1();
    void task2();
    void task3();
public:
    Lesson8();
};

class Track {
public:
    string title;
    struct tm creationDate;
    long duration;

    Track(string title, struct tm creationDate, long duration)
        : title(move(title)), creationDate(creationDate), duration(duration) {}

    friend ostream& operator<<(ostream& os, const Track& track) {
        return os << "Title: " << track.title << ", Created on: "
                  << asctime(&track.creationDate) << ", Duration: "
                  << track.duration << " seconds";
    }
};

class Player {
public:
    vector<Track> tracks;
    Track* currentTrack = nullptr;
    bool isPlaying = false;
    bool isPaused = false;

    void addTrack(const Track& track) {
        tracks.push_back(track);
    }

    void playTrack(const string& title) {
        for (const auto& track : tracks) {
            if (track.title == title) {
                currentTrack = &track;
                isPlaying = true;
                return;
            }
        }
        cout << "Track not found." << endl;
    }

    void pause() {
        if (isPlaying && !isPaused) {
            isPaused = true;
            cout << "Paused." << endl;
        }
    }

    void resume() {
        if (isPlaying && isPaused) {
            isPaused = false;
            cout << "Resumed." << endl;
        }
    }

    void nextTrack() {
        if (tracks.empty()) {
            cout << "No more tracks." << endl;
            return;
        }
        if (currentTrack) {
            int index = tracks.size() - 1;
            uniform_int_distribution<int> dist(0, index);
            default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
            auto nextIndex = dist(engine);
            currentTrack = &tracks[nextIndex];
            cout << "Next track: " << *currentTrack << endl;
        }
    }

    void stop() {
        if (isPlaying) {
            isPlaying = false;
            currentTrack = nullptr;
            cout << "Stopped." << endl;
        }
    }

    void clearTracks() {
        tracks.clear();
        currentTrack = nullptr;
        isPlaying = false;
        isPaused = false;
    }
};

class Contact {
public:
    string name;
    string phoneNumber;

    Contact(string name, string phoneNumber) : name(name), phoneNumber(phoneNumber) {}
};

class Phone {
public:
    vector<Contact> contacts;

    void addContact(const string& name, const string& phoneNumber) {
        contacts.push_back(Contact(name, phoneNumber));
    }

    void call(const string& contactNameOrNumber) {
        for (const auto& contact : contacts) {
            if (contact.name == contactNameOrNumber || contact.phoneNumber == contactNameOrNumber) {
                cout << "CALL " << contact.phoneNumber << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void sendSMS(const string& contactNameOrNumber, const string& message) {
        for (const auto& contact : contacts) {
            if (contact.name == contactNameOrNumber || contact.phoneNumber == contactNameOrNumber) {
                cout << "SEND SMS " << contact.phoneNumber << ": " << message << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }
};

class Window {
public:
    int x, y;
    int w, h;

    Window(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    void move(const std::vector<int>& delta) {
        x += delta[0];
        y += delta[1];
        std::cout << "Window moved to (" << x << "," << y << ")" << std::endl;
    }

    void resize(const std::vector<int>& newSize) {
        w = newSize[0];
        h = newSize[1];
        std::cout << "Window resized to " << w << "x" << h << std::endl;
    }
};

class Screen {
public:
    int width, height;
    std::vector<std::vector<int>> pixels;

    Screen(int width, int height) : width(width), height(height) {
        pixels.resize(width);
        for (auto& row : pixels) {
            row.resize(height);
        }
    }

    void drawWindow(const Window& window) {
        for (int x = 0; x < window.w; ++x) {
            for (int y = 0; y < window.h; ++y) {
                pixels[window.x + x][window.y + y] = 1;
            }
        }
    }

    void eraseWindow(const Window& window) {
        for (int x = 0; x < window.w; ++x) {
            for (int y = 0; y < window.h; ++y) {
                pixels[window.x + x][window.y + y] = 0;
            }
        }
    }

    void draw() {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                std::cout << pixels[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // LESSON8_H
