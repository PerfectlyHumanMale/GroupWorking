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
    //CircleShape s;
    String savedData[9];

    Texture texture;
    Sprite sprite;
public:
    Workers() {
        sprite.setPosition(cargoLocation);
        //s.setFillColor(Color::Red);
        //s.setRadius(20);
        texture.loadFromFile("Spaceman.png");
    }
    void getCargoLocation(Vector2f v) {
        cargoLocation = v;
    }
    void spawn(sf::RenderWindow& wind) {
        sprite.setPosition(Location);
        sprite.setScale(Vector2f(0.03, 0.03));
        //s.setPosition(Location);
        sprite.setTexture(texture);
        //wind.draw(s);
        wind.draw(sprite);
    }
    Vector2f getLocation() {
        return Location;
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

    int Output() {
            if (sprite.getGlobalBounds().contains(RoomLocation)) {
                return 1;
            }
        }
    void setnumber(int num) {
        workerNumber = num;
    }
    int desplaynumber(CircleShape MouseFolllowor, bool click) {
        if (sprite.getGlobalBounds().contains(MouseFolllowor.getPosition()) && !click) {
            cout << workerNumber<< endl;
            return workerNumber;
        }
        return 0;
    }
    int getnumber(){
        return workerNumber;
    }

    void loadFile(string loadedData, RenderWindow& window) {
        string st;
        stringstream ss(loadedData);

        vector<string> v;

        while (getline(ss, st, '|')) {
            v.push_back(st);
        }
        string saveNumber(v[0]);
        string saveX(v[1]);
        string saveY(v[2]);
        string saveHealth(v[3]);
        string saveStrength(v[4]);
        string saveEndurence(v[5]);
        string saveIntelegence(v[6]);
        string::size_type sz;

        health = stoi(saveHealth, &sz);
        strength = stoi(saveStrength, &sz);
        endurence = stoi(saveEndurence, &sz);
        intellegence = stoi(saveIntelegence, &sz);
        workerNumber = stoi(saveNumber, &sz);

        setLocation(Vector2f(stof(saveX, &sz), stof(saveY, &sz)));
        setRoom(Vector2f(0,800));
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