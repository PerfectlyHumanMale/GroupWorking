#ifndef Rooms_H
#define Rooms_H

#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;
class Rooms : public RectangleShape {
    Vector2f Location;
    Texture Sprite;
    
    int roomNumber;
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

    void spawn(RenderWindow& wind) {
        s.setPosition(Location);
        wind.draw(s);
    }
    void setLocation(Vector2f spawnPoint) {
        int x = spawnPoint.x;
        int y = spawnPoint.y;
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
    
    //Types are Green House = 0, Genarater = 1, Kitchen = 2, Elevater = 3
    void determinType(int type, int cargoX) {
        Type = type;
        if (cargoX == getLocation().x) {
            s.setFillColor(Color(100, 0, 0));
        }
        else {
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
            default:
                s.setFillColor(Color(255, 255, 255));
                break;
            }
        }
    }
    Vector2f returnClick(CircleShape MouseFolllowor) {
        if (Keyboard::isKeyPressed(Keyboard::O) && s.getGlobalBounds().contains(MouseFolllowor.getPosition())) {
            cout << to_string(roomNumber);
            return MouseFolllowor.getPosition();
        }
    }
    void setnumber(int num) {
        roomNumber = num;
    }
    Vector2f desplayLocation(CircleShape MouseFolllowor, bool click) {
        if (s.getGlobalBounds().contains(MouseFolllowor.getPosition()) && !click) {
            cout << "clicked ";
            return getLocation();
        }
    }
    String saveData() {
        String saveString = savedData[0] + " | " + savedData[1] + " | " + savedData[2];
        return saveString;
    }
};
#endif