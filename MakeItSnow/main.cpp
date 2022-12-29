#include <SFML/Graphics.hpp> 
// these were include to save space & when time coding
#include <sstream>
#include <iostream>
#include "Rooms.cpp"
#include "Workers.cpp"
#include "Menus.cpp"
using namespace sf;
using namespace std;

// define render window size constants
#define winWidth 1000
#define winHeight 1000

//here is our main game window
CircleShape MouseFolllowor;
Vector2f LocationOfRoom;

void gridview(RenderWindow& wind) {
    vector<RectangleShape> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(RectangleShape());
        v.back().setPosition(i * 100, 0);
        v.back().setFillColor(Color::White);
        v.back().setSize(Vector2f(2, 1000));
        wind.draw(v.back());
    }
    for (int j = 0; j < 10; j++) {
        v.push_back(RectangleShape());
        v.back().setPosition(0, j * 100);
        v.back().setFillColor(Color::White);
        v.back().setSize(Vector2f(1000, 2));
        wind.draw(v.back());
    }
}

int main()
{
    Menus menu;
    
    int metal = 11;
    int t = 0;

    menu.setKey(Keyboard::B);

    bool paused = false;
    bool buildup = false;
    bool click = true;
    Rooms room[100];
    Workers worker[100];
    Rooms CargoHold;
    RenderWindow window(sf::VideoMode(winWidth, winHeight), "Main");
    //define the coordenites on our screen
    int i = 0;

    menu.createMenu(Vector2f(300, 400), Vector2f(300, 100));
    menu.createTab(10);

    //Define the cargo
    CargoHold.setLocation(Vector2f(winWidth / 2, 100));
    CargoHold.setFillColor(Color(255, 255, 255));
    CargoHold.setOutlineColor(Color(255, 255, 255));
    CargoHold.setOutlineThickness(10);

    //run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Resets the window 
        window.clear(Color::Black);

        //Makes the object follow the mouse
        MouseFolllowor.setPosition(Mouse::getPosition().x - 475, Mouse::getPosition().y - 70);
        MouseFolllowor.setRadius(10);
        window.draw(MouseFolllowor);

        RectangleShape r;
        r.setSize(Vector2f(100, 100));

        if (Keyboard::isKeyPressed(Keyboard::G)) {
            metal += 10;
            cout << metal;
        }
        
        gridview(window);

        //Room placement
        if (event.type == Event::MouseButtonPressed && click) {
            click = false;
            bool here = true;
            int x;
            int y;
            x = MouseFolllowor.getPosition().x;
            y = MouseFolllowor.getPosition().y;
            //aviods double placing
            for (int j = 0; j < 100; j++) {
                if (room[j].getLocation() == Vector2f(MouseFolllowor.getPosition().x - (x % 100), MouseFolllowor.getPosition().y - (y % 100))) {
                    here = false;
                }
            }
            if (metal >= 10 && here == true) {
                room[i].setLocation(MouseFolllowor.getPosition());
                cout << MouseFolllowor.getPosition().x << endl;
                cout << MouseFolllowor.getPosition().y << endl;
                room[i].determinType(i % 3, CargoHold.getLocation().x);
                metal -= 10;
            }
            worker[i].setLocation(Vector2f(0, 0));
            i++;
        }
        else if (event.type == Event::MouseButtonReleased) {
            click = true;
        }
        //gameloop
        for (int j = 0; j < 100; j++) {
            room[j].spawn(window);
            worker[j].spawn(window);
            worker[j].moveToRoom(LocationOfRoom, Vector2f(winWidth / 2, 0));
            CargoHold.spawn(window);
            t += worker[j].testOutput(room[i]);
            CargoHold.setFillColor(Color(t, t, t));
        }

        //worker to room
        if (Keyboard::isKeyPressed(Keyboard::O)) {
        //LocationOfRoom = MouseFolllowor.getPosition();
            for (int i = 0; i < 100;i++) {
                if (MouseFolllowor.getGlobalBounds().contains(room[i].getLocation())){
                    LocationOfRoom = room[i].getLocation();
                }
            }
        }
        menu.drawMenu(window);
        // end the current frame
        window.display();
    }
    return 0;
}