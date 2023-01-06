#ifndef Workers_H
#define Workers_H

#include <SFML/Graphics.hpp> 
// these were include to save space & when time coding
#include <sstream>
#include <iostream>
#include "Rooms.cpp"

using namespace sf;
using namespace std;

class Workers {
    String savedX, savedY;
    Texture Sprite;

    Vector2f Location = Vector2f(100,100);
    Vector2f cargoLocation;
    Vector2f RoomLocation;

    String Name;
    double health;
    double strength;
    double intellegence;
    double endurence;
    double maxHealth = endurence * 3;
    int workerNumber;

    Event event;
    CircleShape s;
    String savedData[9];
public:
    Workers() {
        s.setPosition(cargoLocation);
        s.setFillColor(Color::Red);
        s.setRadius(20);
    }
    void getCargoLocation(Vector2f v) {
        cargoLocation = v;
    }
    void spawn(sf::RenderWindow& wind) {
        s.setPosition(Location);
        wind.draw(s);
    }
    void setLocation(Vector2f spawnPoint) {
        Location = spawnPoint;
    }
    void createWorker(int id) {
        Name = "Name: " + id;
        strength = 1;
        intellegence = 1;
        endurence = 1;
    }
    void setRoom(Vector2f room) {
        RoomLocation = room;
    }
    void moveToRoom(Vector2f cargoLocation) {
        if (Location.y == RoomLocation.y && Location.x < RoomLocation.x) {
            Location.x += 1;
        }
        else if (Location.y == RoomLocation.y && Location.x > RoomLocation.x) {
            Location.x -= 1;
        }
        else if (Location.x == cargoLocation.x && Location.y < RoomLocation.y) {
            Location.y += 1;
        }
        else if (Location.x == cargoLocation.x && Location.y > RoomLocation.y) {
            Location.y -= 1;
        }
        else if (Location.y != RoomLocation.y && Location.x < cargoLocation.x) {
            Location.x += 1;
        }
        else if (Location.y != RoomLocation.y && Location.x > cargoLocation.x) {
            Location.x -= 1;
        }
    }

    void testOutput() {
            if (s.getGlobalBounds().contains(RoomLocation)) {
                cout << "l";
            }
        }
    void setnumber(int num) {
        workerNumber = num;
    }
    int desplaynumber(CircleShape MouseFolllowor, bool click) {
        if (s.getGlobalBounds().contains(MouseFolllowor.getPosition()) && !click) {
            cout << "clicked ";
            return workerNumber;
        }
        return 0;
    }

    void loadFile(Vector2f LocationPoint) {
        string saveNumber(savedData[0]);
        string saveX(savedData[1]);
        string saveY(savedData[2]);
        string saveHealth(savedData[3]);
        string saveStrength(savedData[4]);
        string saveEndurence(savedData[5]);
        string saveIntelegence(savedData[6]);
        string::size_type sz;

        Location.x = stod(saveX, &sz);
        Location.y = stod(saveY, &sz);
        health = stod(saveHealth, &sz);
        strength = stod(saveStrength, &sz);
        endurence = stod(saveEndurence, &sz);
        intellegence = stod(saveIntelegence, &sz);
        workerNumber = stod(saveNumber, &sz);
    }
    String saveTheData() {
        savedData[0] = to_string(workerNumber);
        savedData[1] = to_string(Location.x);
        savedData[2] = to_string(Location.y);
        savedData[3] = to_string(health);
        savedData[4] = to_string(strength);
        savedData[5] = to_string(endurence);
        savedData[6] = to_string(intellegence);
        savedData[7] = to_string(RoomLocation.x);
        savedData[8] = to_string(RoomLocation.y);

        String saveString = savedData[0] + " | " + savedData[1] + " | " + savedData[2] + " | " + savedData[3] + " | " + savedData[4] + " | " + savedData[5] + " | " + savedData[6] + " | " + savedData[7] + " | " + savedData[8];
        return saveString;
    }
};
#endif