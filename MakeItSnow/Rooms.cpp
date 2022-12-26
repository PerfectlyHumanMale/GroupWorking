#ifndef Rooms_H
#define Rooms_H

#include <SFML/Graphics.hpp> 
// these were include to save space & when time coding
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;
class Rooms : public RectangleShape {
    Vector2f Location;
    Texture Sprite;
    
    //Workers w[100];
    int oxagen = 10;
    int energy = 10;
    int food = 10;

    int Type;//Types are Green House = 1, Genarater = 2, Kitchen = 3, Elevater = 4

    RectangleShape s;
    String savedData[5];
public:
    Rooms() {
        s.setFillColor(Color::Green);
        s.setSize(Vector2f(100, 100));
    }
    //Types are Green House = 0, Genarater = 1, Kitchen = 2, Elevater = 3
    
    void determinType(int type) {
        Type = type;
        switch (type) {
        case 0:
            s.setFillColor(Color(0, 200, 0));
            break;
        case 1:
            s.setFillColor(Color(200, 0, 0));
            break;
        case 2:
            s.setFillColor(Color(0, 0, 200));
            break;
        case 3:
            s.setFillColor(Color(200, 200, 200));
            break;
        }
    }
    void spawn(sf::RenderWindow& wind) {
        s.setPosition(Location);
        wind.draw(s);
    }
    void setLocation(Vector2f spawnPoint) {
        int x;
        int y;
        x = spawnPoint.x;
        y = spawnPoint.y;
        Location = Vector2f(spawnPoint.x - (x % 100), spawnPoint.y - (y % 100));
    }
    Vector2f getLocation() {
        return Location;
    }

    void loadFile(Vector2f LocationPoint) {
        string saveX(savedData[0]);
        string saveY(savedData[1]);
        string saveType(savedData[2]);
        string::size_type sz;     // alias of size_t

        Location.x = stod(saveX, &sz);
        Location.y = stod(saveY, &sz);

        Type = stod(saveType, &sz);
    }
    void CalulateOutput() {
        int workers;
        switch (Type) {
        case 1:
            oxagen += 1;
            break;
        case 2:
            energy += 1;
            break;
        case 3:
            food += 1;
            break;
        }
        return;

    }
    
    String saveData() {
        String saveString = savedData[0] + " | " + savedData[1] + " | " + savedData[2];
        return saveString;
    }
};
#endif