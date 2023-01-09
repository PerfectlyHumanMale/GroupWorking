#ifndef Rooms_H
#define Rooms_H

#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Workers.cpp"

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
    //vector <string> savedData;
    string savedData[4];
public:
    Rooms() {
        s.setFillColor(Color::Green);
        s.setSize(Vector2f(100, 100));
    }

    void spawn(RenderWindow& wind) {
        s.setPosition(Location);
        wind.draw(s);
    }
    Vector2f getLocation() {
        return Location;
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

    int Output(Workers workers[100]) {
        for (int i = 0; i < 100; ) {
            if (s.getGlobalBounds().contains(workers[i].getLocation())) {
                return 1;
            }
        }
    }
    int getType() {
        return Type;
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
            //cout << "clicked ";
            return getLocation();
        }
    }
    String saveData() { 
        savedData[0] = to_string( s.getPosition().x);
        savedData[1] = to_string( s.getPosition().y);
        savedData[2] = to_string( Type);

        String saveString = savedData[0] + " | " + savedData[1] + " | " + savedData[2];
        return saveString;
    }
    void loadFile(string loadedData, RenderWindow& window) {
        string st;
        stringstream ss(loadedData);

        vector<string> v;

        while (getline(ss, st, '|')) {
            v.push_back(st);
        }

        string saveX( v[0]);
        string saveY(v[1]);
        string saveType(v[2]);
        string::size_type sz;
        setLocation(Vector2f( stof(saveX, &sz), stof(saveY, &sz)));
        determinType(stoi(saveType, &sz), window.getSize().x/2);
        
        //Type = stoi(saveType, &sz);
        window.draw(s);
    }
    void setLocation(Vector2f spawnPoint) {
        int x = spawnPoint.x;
        int y = spawnPoint.y;
        Location = Vector2f(spawnPoint.x - (x % 100), spawnPoint.y - (y % 100));
    }
};
#endif