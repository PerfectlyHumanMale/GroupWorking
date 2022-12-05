#include <SFML/Graphics.hpp> 
// these were include to save space & when time coding
#include <sstream>
#include <iostream>
using namespace sf;
using namespace std;

class Workers {
    String savedX, savedY;
    Vector2f Location;
    Vector2f Velocity;
    Texture Sprite;

    Vector2f cargoLocation;

    String Name;
    double health;
    double strength;
    double intellegence;
    double endurence;
    double maxHealth = endurence * 3;

    CircleShape s;
    String savedData[8];
public:
    Workers() {
        s.setPosition(cargoLocation);
        s.setFillColor(Color::Red);
        s.setRadius(10);
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
    void loadFile(Vector2f LocationPoint) {
        string saveX(savedData[1]);
        string saveY(savedData[2]);
        string saveHealth(savedData[3]);
        string saveStrength(savedData[4]);
        string saveEndurence(savedData[5]);
        string saveIntelegence(savedData[6]);
        string saveName(savedData[7]);
        string::size_type sz;     // alias of size_t

        Location.x = stod(saveX, &sz);
        Location.y = stod(saveY, &sz);
        health = stod(saveHealth, &sz);
        strength = stod(saveStrength, &sz);
        endurence = stod(saveEndurence, &sz);
        intellegence = stod(saveIntelegence, &sz);
        Name = savedData[0];
    }
    void saveData() {
        String saveString = savedData[0] + " | " + savedData[1] + " | " + savedData[2] + " | " + savedData[3] + " | " + savedData[4] + " | " + savedData[5] + " | " + savedData[6] + " | " + savedData[7];
    }
    void createWorker(int id) {
        Name = "Name: " + id;
        strength = 1;
        intellegence = 1;
        endurence = 1;
    }
    void moveToRoom(Vector2f roomLocation, Vector2f cargoLocation) {
        if (Location.y == roomLocation.y && Location.x <= cargoLocation.x) {
            Location.x += 1;
        }
        else if (Location.y == roomLocation.y && Location.x >= cargoLocation.x) {
            Location.x -= 1;
        }
        else if (Location.x == cargoLocation.x && Location.y <= roomLocation.y) {
            Location.y += 1;
        }
        else if (Location.x == cargoLocation.x && Location.y >= roomLocation.y) {
            Location.y -= 1;
        }
        else if (Location.y != roomLocation.y && Location.x <= cargoLocation.x) {
            Location.x += 1;
        }
        else if (Location.y != roomLocation.y && Location.x >= cargoLocation.x) {
            Location.x -= 1;
        }
    }
};