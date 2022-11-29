#include <SFML/Graphics.hpp> 
// these were include to save space & when time coding
#include <sstream>
#include <iostream>
#include "Rooms.cpp"
#include "Workers.cpp"
using namespace sf;
using namespace std;

// define render window size constants
#define winWidth 1000
#define winHeight 1000

//here is our main game window
CircleShape MouseFolllowor;
int main()
{
    int metal = 11;

    bool click = true;
    Rooms room[100];
    Workers worker[100];
    Rooms CargoHold;
    RenderWindow window(sf::VideoMode(winWidth, winHeight), "My window");
    //define the coordenites on our screen
    int i = 0;

    //run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //Define the cargo
        CargoHold.setLocation(Vector2f(winWidth / 2, 100));
        CargoHold.spawn(window);
        CargoHold.setFillColor(Color(50, 50, 50));
        CargoHold.setOutlineColor(Color(200, 200, 200));
        CargoHold.setOutlineThickness(10);

        // Resets the window 
        window.clear(sf::Color::Black);

        //Makes the object follow the mouse
        MouseFolllowor.setPosition(Mouse::getPosition().x - 475, Mouse::getPosition().y - 70);
        MouseFolllowor.setRadius(10);
        window.draw(MouseFolllowor);

        RectangleShape r;
        r.setSize(Vector2f(100, 100));

        vector<RectangleShape> v;
        bool gridview = false;
        if (Keyboard::isKeyPressed(Keyboard::G)) {
            metal += 10;
            cout << metal;
        }
        for (int i = 0; i < 10; i++) {
            v.push_back(RectangleShape());
            v.back().setPosition(i * 100, 0);
            v.back().setFillColor(Color::White);
            v.back().setSize(Vector2f(2, 1000));
            window.draw(v.back());
        }
        for (int j = 0; j < 10; j++) {
            v.push_back(RectangleShape());
            v.back().setPosition(0, j * 100);
            v.back().setFillColor(Color::White);
            v.back().setSize(Vector2f(1000, 2));
            window.draw(v.back());
        }
        //}
        if (event.type == Event::MouseButtonPressed && click) {
            click = false;
            bool here = true;
            int x;
            int y;
            x = MouseFolllowor.getPosition().x;
            y = MouseFolllowor.getPosition().y;
            for (int j = 0; j < 100; j++) {
                if (room[j].getLocation() == Vector2f(MouseFolllowor.getPosition().x - (x % 100), MouseFolllowor.getPosition().y - (y % 100))) {
                    here = false;
                }
            }
            if (metal >= 10 && here == true) {
                room[i].setLocation(MouseFolllowor.getPosition());
                cout << MouseFolllowor.getPosition().x << endl;
                cout << MouseFolllowor.getPosition().y << endl;
                room[i].determinType(i % 3);
            }
            metal-=10;
            worker[i].setLocation(Vector2f(0, 0));
            i++;
        }
        else if (event.type == Event::MouseButtonReleased) {
            click = true;
        }
        for (int j = 0; j < 100; j++) {
            room[j].spawn(window);
            worker[j].spawn(window);
            worker[j].moveToRoom(Vector2f(100, 100), Vector2f(winWidth / 2, 0));
        }
        // end the current frame
        window.display();
    }
    return 0;
}