#pragma region imports
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include "Rooms.cpp"
#include "Workers.cpp"
#include "Menus.cpp"
using namespace sf;
using namespace std;
#pragma endregion imports

#pragma region publicVerables 
CircleShape MouseFolllowor;
Vector2f LocationOfRoom;
#define winWidth 1100
#define winHeight 1000
Menus MinigameMenu;
Menus WorkerMenu;
Menus BuildMenu;
int metal = 11;
int t = 0;
bool paused = false;
bool buildup = false;
bool click = true;
Rooms room[100];
Workers worker[100];
Rooms CargoHold;
RenderWindow window(sf::VideoMode(winWidth, winHeight), "Main");
int i = 0;
#pragma endregion publicVerables 

void gridview(RenderWindow& wind) {
    vector<RectangleShape> v;
    for (int i = 0; i < 11; i++) {
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
        v.back().setSize(Vector2f(1100, 2));
        wind.draw(v.back());
    }
}
#pragma region menuMethods
void CreatWorker(bool on) {
    
}
void BuildRoom(bool on, int type) {

}
void OpenGame(bool on, int gamenumber) {

}
#pragma endregion menuMethods

int main()
{
    #pragma region defineMenu 
    MinigameMenu.setKey(Keyboard::B);
    MinigameMenu.createMenu(Vector2f(300, 400), Vector2f(300, 100));
    MinigameMenu.createTab(6);

    WorkerMenu.setKey(Keyboard::N);
    WorkerMenu.createMenu(Vector2f(300, 400), Vector2f(0, 0));
    WorkerMenu.createTab(6);

    BuildMenu.setKey(Keyboard::M);
    BuildMenu.createMenu(Vector2f(300, 400), Vector2f(800, 0));
    BuildMenu.createTab(6);
    #pragma endregion defineMenu

    #pragma region defineCargo
    CargoHold.setLocation(Vector2f(winWidth / 2, 100));
    CargoHold.setFillColor(Color(255, 255, 255));
    CargoHold.setOutlineColor(Color(255, 255, 255));
    CargoHold.setOutlineThickness(10);
    #pragma endregion defineCargo

    #pragma region houseKeeping
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear(Color::Black);
       #pragma endregion houseKeeping

        #pragma region buttonStuff
        if (Keyboard::isKeyPressed(Keyboard::H)) {
            metal += 10;
            cout << metal;
        }
        if (Keyboard::isKeyPressed(Keyboard::G)) {
            gridview(window);
        }
        if (Keyboard::isKeyPressed(Keyboard::O)) {
            //LocationOfRoom = MouseFolllowor.getPosition();
            for (int i = 0; i < 100;i++) {
                if (MouseFolllowor.getGlobalBounds().contains(room[i].getLocation())) {
                    LocationOfRoom = room[i].getLocation();
                }
            }
        }
        #pragma endregion buttonStuff

        #pragma region RoomPlacement
        if (event.type == Event::MouseButtonPressed && click) {
            click = false;
            bool here = true;
            int x = MouseFolllowor.getPosition().x;
            int y = MouseFolllowor.getPosition().y;
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
        #pragma endregion RoomPlacement

        #pragma region Gameloop
        for (int j = 0; j < 100; j++) {
            CargoHold.spawn(window);
            t += worker[j].testOutput(room[i]);
            CargoHold.setFillColor(Color(t, t, t));

            room[i].returnClick(MouseFolllowor);
            room[j].spawn(window);

            worker[j].spawn(window);
            worker[j].moveToRoom(Vector2f(100, 300), Vector2f(winWidth / 2, 0));
            worker[j].desplaynumber(MouseFolllowor, click);

            WorkerMenu.drawMenu(window);
            BuildMenu.drawMenu(window);
            MinigameMenu.drawMenu(window);
        }
        #pragma endregion Gameloop

        #pragma region defineMouse
        MouseFolllowor.setPosition(Mouse::getPosition().x - 475, Mouse::getPosition().y - 70);
        MouseFolllowor.setRadius(10);
        window.draw(MouseFolllowor);
        #pragma endregion defineMouse
        window.display();
    }
    return 0;
}